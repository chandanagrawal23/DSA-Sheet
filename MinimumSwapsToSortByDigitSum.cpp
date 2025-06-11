#include <vector>
#include <array>
#include <algorithm>

using namespace std;

/* Sort by digit-sum first, then by actual value */
bool compare(const array<int,3>& a, const array<int,3>& b)
{
    if (a[0] != b[0]) return a[0] < b[0];   // primary key
    return a[1] < b[1];                     // tie-breaker
}

class Solution
{
public:
    /* Return sum of decimal digits of num */
    int digitSum(int num)
    {
        int s = 0;
        while (num)
        {
            s += num % 10;
            num /= 10;
        }
        return s;
    }

    /* Minimum swaps to sort by digit-sum (then value) */
    int minSwaps(vector<int>& nums)
    {
        int n = nums.size();
        vector<array<int,3>> info;                  // {digitSum, value, originalIdx}

        for (int i = 0; i < n; ++i)
            info.push_back({ digitSum(nums[i]), nums[i], i });

        sort(info.begin(), info.end(), compare);    // arrange by desired order

        vector<char> vis(n, 0);
        int swaps = 0;

        /* Cycle decomposition of permutation */
        for (int i = 0; i < n; ++i)
        {
            if (vis[i] || info[i][2] == i) continue;

            int cycle = 0, j = i;
            while (!vis[j])
            {
                vis[j] = 1;
                j = info[j][2];                     // jump to element’s original slot
                ++cycle;
            }
            swaps += cycle - 1;                     // swaps for this cycle
        }
        return swaps;
    }
};

/*
Approach (brief):
1.  Build array {digitSum, value, originalIdx}.
2.  Sort by (digitSum, value) using a simple function comparator.
3.  The sorted order defines a permutation of indices.
4.  Minimum swaps = Σ (cycleSize − 1) over all cycles in that permutation.

Time:  O(n log n)  (sorting dominates)
Space: O(n)        (info + visited arrays)
*/

/*

NICE EXPLAINATION 

https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/solutions/6760520/answer-to-your-why-intuition-disjoint-cycle-and-swaps-relation-c/


*/
