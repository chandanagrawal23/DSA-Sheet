class Solution
{
public:
    int getMaxProduct(int remainingSum, int maxAllowed, vector<vector<int>>& dp)
    {
        // Base case: can't split further
        if (remainingSum == 0 || maxAllowed == 0)
        {
            return 1;
        }

        // Return cached result
        if (dp[remainingSum][maxAllowed] != -1)
        {
            return dp[remainingSum][maxAllowed];
        }

        // Skip numbers greater than remaining
        if (maxAllowed > remainingSum)
        {
            return dp[remainingSum][maxAllowed] = getMaxProduct(remainingSum, maxAllowed - 1, dp);
        }

        // Option 1: take current number and multiply with result of breaking remaining
        int take = maxAllowed * getMaxProduct(remainingSum - maxAllowed, maxAllowed, dp);

        // Option 2: skip current number
        int skip = getMaxProduct(remainingSum, maxAllowed - 1, dp);

        return dp[remainingSum][maxAllowed] = max(take, skip);
    }

    int integerBreak(int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1)); 
        return getMaxProduct(n, n - 1, dp);
    }
};

/*
Approach:
- Break integer n into a sum of at least two positive integers to maximize their product.
- Try all numbers from n-1 down to 1.
- For each number, either include it (and recurse) or skip it.
- Return the maximum product formed from valid partitions.

Time Complexity: O(n^2) with memoization
Space Complexity: O(n^2) for dp table + O(n) recursive stack depth
*/
