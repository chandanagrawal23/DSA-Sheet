class Solution 
{
public:

    // Main function to compute minimum insertions to make string a palindrome
    int minInsertions(string s) 
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));  // DP table initialized with -1
        return minInsertionsHelper(s, 0, n - 1, dp);
    }

    // Helper function using recursion + memoization
    int minInsertionsHelper(string &s, int i, int j, vector<vector<int>> &dp) 
    {
        // Base case: single char or empty substring is already a palindrome
        if (i >= j)
            return 0;

        // Return previously computed value
        if (dp[i][j] != -1)
            return dp[i][j];

        // If characters match, move inward
        if (s[i] == s[j])
        {
            return dp[i][j] = minInsertionsHelper(s, i + 1, j - 1, dp);
        }

        // Else, insert at either end and take minimum
        return dp[i][j] = min(
            1 + minInsertionsHelper(s, i, j - 1, dp),   // Insert at end
            1 + minInsertionsHelper(s, i + 1, j, dp)    // Insert at start
        );
    }
};

/*
Approach:
- Use recursion + memoization to find the minimum insertions required
  to make the string a palindrome.
- If characters at both ends match, move inward.
- Otherwise, try inserting at either end and take the minimum.

Time Complexity:  O(n^2)
Space Complexity: O(n^2)
*/
