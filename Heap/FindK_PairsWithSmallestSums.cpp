#include <bits/stdc++.h>
using namespace std;

class cmp
{
public:
    bool operator()(vector<int> &a, vector<int> &b)
    {
        // Min-heap based on sum of pairs
        return (a[0] + a[1]) > (b[0] + b[1]);
    }
};

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

        int n = nums1.size();
        int m = nums2.size();

        // Push first k pairs from nums1 with the first element of nums2
        for (int i = 0; i < min(k, n); i++)
        {
            pq.push({nums1[i], nums2[0], 0}); // (num1, num2, index_in_nums2)
        }

        vector<vector<int>> result;

        while (k-- && !pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();

            int value_from_nums1 = cur[0];
            int value_from_nums2 = cur[1];
            int index = cur[2];

            result.push_back({value_from_nums1, value_from_nums2});

            // Push next pair with same num1 but next num2
            if ((index + 1) < m)
            {
                pq.push({value_from_nums1, nums2[index + 1], index + 1});
            }
        }

        return result;
    }
};

/*
Approach: Min Heap — O(k log k)
===============================

We are given two sorted arrays nums1 and nums2.
We want to return the k pairs (nums1[i], nums2[j]) with the smallest sums.

Observation:
------------
- Pair sums form an n x m matrix, where matrix[i][j] = nums1[i] + nums2[j]
- This matrix is sorted row-wise and column-wise due to input being sorted

Optimization:
-------------
- Instead of generating all n*m pairs, we simulate traversal using a min heap
- Start by inserting first `min(k, nums1.size())` pairs: (nums1[i], nums2[0])
  → These are the first elements (leftmost) of each row — the most promising

Process:
--------
1. Heap stores: (num1, num2, j), where j is the index in nums2
2. Each time we pop the smallest pair:
   - Add it to result
   - Push (num1, nums2[j+1], j+1) — the next column in same row, if valid

Why only first k rows?
----------------------
- Because (nums1[k], nums2[0]) and beyond can’t give smaller sums than the k already in heap
- If they could, they’d be surfaced by heap during pops and expansions

Time & Space:
-------------
- Time: O(k log k) — At most k heap operations
- Space: O(k) — For heap and output

*/

