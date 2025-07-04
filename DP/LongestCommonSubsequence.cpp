class Solution 
{
public:

    // Main function to compute LCS
    int longestCommonSubsequence(string a, string b) 
    {
        int n = a.size();
        int m = b.size();

        // Initialize DP table with -1
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        return lcsHelper(a, b, n, m, dp);
    }

    // Recursive LCS with memoization
    int lcsHelper(string &a, string &b, int i, int j, vector<vector<int>> &dp) 
    {
        // Base case: if either string is empty
        if (i == 0 || j == 0)
            return 0;

        // Return memoized result
        if (dp[i][j] != -1)
            return dp[i][j];

        // both char's match
        if (a[i - 1] == b[j - 1])
            return dp[i][j] = 1 + lcsHelper(a, b, i - 1, j - 1, dp);

        // Else, take max by skipping one character from either string
        return dp[i][j] = max(
            lcsHelper(a, b, i - 1, j, dp),
            lcsHelper(a, b, i, j - 1, dp)
        );
    }
};

/*
Approach:
- Use recursion with memoization (top-down DP) to compute LCS.
- If characters match, move diagonally.
- Else, skip one character from either string and take max.

Time Complexity:  O(n * m)
Space Complexity: O(n * m)
*/

/*
// Reconstruct the LCS from the DP table
string lcs = "";
int i = n, j = m;

while (i > 0 && j > 0) 
{
    if (a[i - 1] == b[j - 1]) 
    {
        lcs += a[i - 1];
        i--; j--;
    } 
    else if (dp[i - 1][j] > dp[i][j - 1]) 
    {
        i--;
    } 
    else 
    {
        j--;
    }
}

reverse(lcs.begin(), lcs.end());  // Reversed during backtracking
return lcs;

*/
