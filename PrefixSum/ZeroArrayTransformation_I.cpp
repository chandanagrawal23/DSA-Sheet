#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<int> diff(n + 1, 0); // difference array for range operations

        // Apply each query as a range decrement using 1D difference array
        for (auto &q : queries)
        {
            int l = q[0];
            int r = q[1];

            diff[l] += 1; // start decrement at index l

            if (r + 1 < n)
            {
                diff[r + 1] -= 1; // cancel decrement after index r
            }
        }

        // Build prefix sum of operations array
        for (int i = 1; i < n; i++)
        {
            diff[i] += diff[i - 1];
        }

        // Check if each element in nums can be reduced to zero
        for (int i = 0; i < n; i++)
        {
            if (diff[i] < nums[i])
            {
                return false; // not enough decrements applied at index i
            }
        }

        return true;
    }
};

/*
Approach:
- For each query [l, r], we can choose a subset of indices to decrement.
- To maximize reduction power, we greedily choose to decrement *all* indices in [l, r].

- To handle all range updates efficiently:
    → Use a 1D difference array `diff[]`.
    → For each query: do `diff[l] += 1` and `diff[r+1] -= 1`.

- Convert difference array to actual prefix sum, which tells us
  how many times each index has been decremented in total.

- If at any index `i`, total decrements < nums[i], then it's
  impossible to reduce nums[i] to zero → return false.

Time Complexity: O(n + q)
Space Complexity: O(n)
*/
