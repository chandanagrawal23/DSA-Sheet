class Solution 
{
public:
    int findMaxForm(vector<string>& strs, int m, int n) 
    {
        int sz = strs.size();

        // 3D DP vector initialized with -1
        vector<vector<vector<int>>> dp(sz, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

        return recur(strs, 0, m, n, dp);
    }

private:
    int recur(vector<string>& strs, int i, int m, int n, vector<vector<vector<int>>>& dp)
    {
        if (i == strs.size())
        {
            return 0; // No more strings
        }

        if (dp[i][m][n] != -1)
        {
            return dp[i][m][n]; // Return cached result
        }

        int count0 = 0, count1 = 0;

        // Count 0s and 1s in current string
        for (char ch : strs[i])
        {
            if (ch == '0') count0++;
            else count1++;
        }

        int take = 0;

        // If we can take the current string
        if (count0 <= m && count1 <= n)
        {
            take = 1 + recur(strs, i + 1, m - count0, n - count1, dp);
        }

        // Skip current string
        int skip = recur(strs, i + 1, m, n, dp);

        // Store and return the best of both choices
        return dp[i][m][n] = max(take, skip);
    }
};

/*
Approach:
- This is a 0/1 Knapsack-style problem.
- For each string, count its 0s and 1s and decide to take or skip it.
- Use 3D memoization: dp[i][m][n] = max strings from index i with m 0s and n 1s left.

Time Complexity: O(L * m * n), where L = strs.size()
Space Complexity: O(L * m * n) for the DP table (vector-based)
*/
