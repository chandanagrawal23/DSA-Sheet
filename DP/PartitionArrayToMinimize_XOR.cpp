#include <bits/stdc++.h>
using namespace std;

class Solution 
{
    // Recursive function to minimize the maximum XOR of k contiguous partitions starting at index i
    int solve(int i, const vector<int> &nums, int k, vector<vector<int>> &dp) 
    {
        if (i == nums.size()) 
            return (k == 0) ? 0 : INT_MAX; // Valid if no partitions left exactly at end, else invalid

        if (k == 0) 
            return INT_MAX;  // Can't partition further if no groups left but elements remain

        if (dp[i][k] != -1) 
            return dp[i][k];  // Return cached result

        // XOR of all remaining elements if only one group left
        if (k == 1) 
        {
            int xorVal = 0;
            for (int j = i; j < nums.size(); ++j)
                xorVal ^= nums[j];  

            return dp[i][k] = xorVal;
        }

        int ans = INT_MAX;
        int currXor = 0;

        // Try all possible partitions starting at index i
        for (int j = i; j < nums.size(); ++j) 
        {
            currXor ^= nums[j];  // XOR for current partition [i..j]

            int next = solve(j + 1, nums, k - 1, dp); // Recurse for remaining partitions

            ans = min(ans, max(currXor, next)); // Minimize the maximum XOR among partitions
        }

        return dp[i][k] = ans; // Cache result
    }

public:
    int minXor(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));  // Memo table
        return solve(0, nums, k, dp);
    }
};

int main()
{
    Solution sol;

    vector<int> tc1 = {1, 2, 3, 4, 5};
    int k1 = 2;
    cout << "Test Case 1 result: " << sol.minXor(tc1, k1) << "\n";

    vector<int> tc2 = {5, 1, 7, 3};
    int k2 = 3;
    cout << "Test Case 2 result: " << sol.minXor(tc2, k2) << "\n";

    return 0;
}

/*
Approach:
- Use recursion + memoization to try all contiguous partitions starting from index i into k groups.
- Calculate XOR of the current partition as we expand it.
- Recursively solve for remaining partitions, and keep track of the minimum possible maximum XOR.
- Memoize results to avoid recomputation.

Time Complexity:
- O(n^2 * k), where n = array length, due to trying all partitions and k groups.

Space Complexity:
- O(n * k) for dp memoization + O(n) recursion stack.
*/
