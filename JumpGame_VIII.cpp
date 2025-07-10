#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& costs) 
    {
        int n = nums.size();

        // Step 1: Build graph where g[i] stores valid jumps from i to j
        // We use two monotonic stacks to build edges as per the problem's conditions
        vector<int> g[n];

        // First Pass: Use monotonic increasing stack to build edges for Rule 1
        // Rule 1: nums[i] <= nums[j] and all elements in (i, j) are < nums[i]
        stack<int> stk;
        for (int i = n - 1; i >= 0; --i)
        {
            // Maintain increasing stack from right to left
            while (!stk.empty() && nums[stk.top()] < nums[i])
                stk.pop();

            if (!stk.empty())
                g[i].push_back(stk.top());  // Valid jump from i -> stk.top() aka j ( chote se bade ki taraf)

            stk.push(i);
        }

        // Second Pass: Use monotonic decreasing stack to build edges for Rule 2
        // Rule 2: nums[i] > nums[j] and all elements in (i, j) are >= nums[i]
        while (!stk.empty()) stk.pop(); // Clear the stack

        for (int i = n - 1; i >= 0; --i)
        {
            // Maintain decreasing stack from right to left
            while (!stk.empty() && nums[stk.top()] >= nums[i])
                stk.pop();

            if (!stk.empty())
                g[i].push_back(stk.top());  // Valid jump from i -> stk.top() aka j ( bade se chote ki taraf)

            stk.push(i);
        }

        // Step 2: Initialize DP array to store minimum cost to reach each index
        vector<long long> f(n, 1e18);
        f[0] = 0;  // Starting at index 0 costs nothing

        // Step 3: Relax all edges using standard DP on DAG approach
        for (int i = 0; i < n; ++i)
        {
            for (int j : g[i])
            {
                // Update cost to reach j if going through i is cheaper
                f[j] = min(f[j], f[i] + costs[j]);
            }
        }

        return f[n - 1];  // Minimum cost to reach last index
    }
};


int main() {
    Solution sol;
    vector<int> nums = {3, 2, 4, 4, 1};
    vector<int> costs = {3, 7, 6, 4, 2};
    cout << "Minimum cost to reach last index: " << sol.minCost(nums, costs) << endl;
    return 0;
}

/*
Explanation:
-----------
We need to compute the minimum cost to reach the last index following specific jump rules.

To do this efficiently:
1. We build a jump graph g[i] using two monotonic stacks:
   - Rule 1 (nums[i] <= nums[j]): strictly increasing jump with smaller mid elements
   - Rule 2 (nums[i] > nums[j]): strictly decreasing jump with greater/equal mid elements

2. From each index i, we only add ONE edge from each rule:
   - One from the increasing stack (next larger/equal)
   - One from the decreasing stack (next smaller)
=> So, each node has at most 2 outgoing edges (max 2 * n total edges)

3. We then use dynamic programming:
   - f[i] = min cost to reach index i
   - f[0] = 0
   - For each jump i -> j, update f[j] = min(f[j], f[i] + costs[j])


We are given an array `nums`, and allowed to jump from index `i` to `j` (i < j) under the following rules:

Rule 1 (Increasing):
- nums[i] <= nums[j] AND all elements between i and j are strictly less than nums[i]

Rule 2 (Decreasing):
- nums[i] > nums[j] AND all elements between i and j are greater than or equal to nums[i]

──────────────────────────────────────────────────────────
    nums  = {3, 2, 4, 4, 1};
    costs = {3, 7, 6, 4, 2};
    
Rule 1 Edge Building (Using Increasing Monotonic Stack)

| i | nums[i] | Stack before | Stack after | Edge i → j |
|---|---------|--------------|-------------|------------|
| 4 |   1     | []           | [4]         | -          |
| 3 |   4     | [4]          | [3]         | 3 → 4      |
| 2 |   4     | [3]          | [2]         | 2 → 3      |
| 1 |   2     | [2]          | [2,1]       | 1 → 2      |
| 0 |   3     | [2,1]        | [0]         | 0 → 2      |

Rule 2 Edge Building (Using Decreasing Monotonic Stack)

| i | nums[i] | Stack before | Stack after | Edge i → j |
|---|---------|--------------|-------------|------------|
| 4 |   1     | []           | [4]         | -          |
| 3 |   4     | [4]          | [3]         | 3 → 4      |
| 2 |   4     | [3]          | [2]         | 2 → 4      |
| 1 |   2     | [2]          | [1]         | 1 → 4      |
| 0 |   3     | [1]          | [0]         | 0 → 1      |

Final Valid Edges (Union of Both Rules):
- 0 → 1
- 0 → 2
- 1 → 2
- 1 → 4
- 2 → 3
- 2 → 4
- 3 → 4

──────────────────────────────────────────────────────────
 DP Transitions:
- f[0] = 0
- f[1] = min(INF, f[0] + 7) = 7
- f[2] = min(INF, f[0] + 6) = 6
- f[2] = min(6, f[1] + 6) = 6
- f[4] = min(INF, f[1] + 2) = 9
- f[3] = min(INF, f[2] + 4) = 10
- f[4] = min(9, f[2] + 2) = 8
- f[4] = min(8, f[3] + 2) = 8

 Final DP array: [0, 7, 6, 10, 8]
Minimum cost to reach last index = f[4] = 8
*/
