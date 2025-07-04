// Approach 1 : Recursion + Memoization
class Solution 
{
public:
    int findLength(vector<int>& A, vector<int>& B) 
    {
        int n = A.size();
        int m = B.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));  // DP declared locally
        int maxLen = 0;

        // Check longest suffix for every (i, j) pair
        for (int i = 1; i <= n; i++) 
        {
            for (int j = 1; j <= m; j++) 
            {
                maxLen = max(maxLen, LCSuffix(A, B, i, j, dp));
            }
        }

        return maxLen;
    }

    int LCSuffix(vector<int>& A, vector<int>& B, int i, int j, vector<vector<int>>& dp) 
    {
        if (i == 0 || j == 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (A[i - 1] == B[j - 1]) 
        {
            return dp[i][j] = 1 + LCSuffix(A, B, i - 1, j - 1, dp);
        }

        return dp[i][j] = 0;
    }
};

/*
Approach:
- Use recursion + memoization to compute the length of the longest common subarray.
- LCSuffix(i, j) gives length of the common subarray ending at A[i-1] and B[j-1].
- Try all (i, j) pairs and find the maximum.
- Matching must be contiguous, so reset on mismatch.

Time Complexity:  O(n * m)
Space Complexity: O(n * m)
*/


// Approach 2 : Iterative DP / Bottom Up DP

class Solution 
{
public:
    int findLength(vector<int>& A, vector<int>& B) 
    {
        int n = A.size();
        int m = B.size();
        int maxLen = 0;

        // dp[i][j] = length of common subarray ending at A[i-1], B[j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) 
        {
            for (int j = 1; j <= m; j++) 
            {
                if (A[i - 1] == B[j - 1]) 
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
                // No else block; if A[i-1] != B[j-1], dp[i][j] stays 0
            }
        }

        return maxLen;
    }
};
