class Solution 
{
public:

    // Recursive function to compute LCS with memoization
    int computeLCS(string &str1, string &str2, int len1, int len2, vector<vector<int>> &dp) 
    {
        // Base case: if either string is empty
        if (len1 == 0 || len2 == 0)
            return 0;

        // Return already computed subproblem
        if (dp[len2][len1] != -1)
            return dp[len2][len1];

        // If characters match, include it and move diagonally
        if (str1[len1 - 1] == str2[len2 - 1])
        {
            return dp[len2][len1] = 1 + computeLCS(str1, str2, len1 - 1, len2 - 1, dp);
        }

        // Otherwise, take max by excluding one character from either string
        return dp[len2][len1] = max(
            computeLCS(str1, str2, len1 - 1, len2, dp),
            computeLCS(str1, str2, len1, len2 - 1, dp)
        );
    }

    int longestPalindromeSubseq(string s) 
    {
        int n = s.size();

        // Create reversed version of string
        string reversed = s;
        reverse(reversed.begin(), reversed.end());

        // Initialize 2D DP table with -1 (for memoization)
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        // LCS of s and reversed(s) gives the length of longest palindromic subsequence
        return computeLCS(s, reversed, n, n, dp);
    }
};

/*
Approach:
- The Longest Palindromic Subsequence (LPS) is the same as the Longest Common Subsequence (LCS)
  between the original string and its reversed version.
- We use recursive LCS with memoization using a 2D DP vector to avoid recomputation.

Time Complexity:  O(n^2) where n = length of the string
Space Complexity: O(n^2) for the 2D memoization table
*/
