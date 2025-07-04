class Solution 
{
public:

    // Public method to compute edit distance
    int minDistance(string word1, string word2) 
    {
        int len1 = word1.length();
        int len2 = word2.length();

        // Declare and initialize memoization table locally
        vector<vector<int>> memo(len1 + 1, vector<int>(len2 + 1, -1));

        return computeEditDistance(word1, word2, len1, len2, memo);
    }

    // Recursive function to compute edit distance with memoization
    int computeEditDistance(string &word1, string &word2, int i, int j, vector<vector<int>> &memo) 
    {
        // If word1 is empty, insert all of word2
        if (i == 0)
        {
            return j;
        }

        // If word2 is empty, delete all of word1
        if (j == 0)
        {
            return i;
        }

        // Return if already computed
        if (memo[i][j] != -1)
        {
            return memo[i][j];
        }

        // If characters match, move diagonally without operation
        if (word1[i - 1] == word2[j - 1])
        {
            return memo[i][j] = computeEditDistance(word1, word2, i - 1, j - 1, memo);
        }

        // Otherwise try insert, delete, and replace
        int insertOp  = computeEditDistance(word1, word2, i, j - 1, memo);
        int deleteOp  = computeEditDistance(word1, word2, i - 1, j, memo);
        int replaceOp = computeEditDistance(word1, word2, i - 1, j - 1, memo);

        return memo[i][j] = 1 + min({insertOp, deleteOp, replaceOp});
    }
};

/*
Approach:
- We compute the minimum number of operations to convert word1 to word2 using recursion + memoization.
- At each step, we either insert, delete, or replace a character and recurse accordingly.
- The memoization table stores results of subproblems to avoid recomputation.

Time Complexity:  O(n * m), where n = length of word1, m = length of word2
Space Complexity: O(n * m), for memoization table
*/
