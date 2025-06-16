// Recursion + Memoization ( 2D DP )

class Solution {
public:
    // Recursive DP with memoization to find minimum coins from index 'cur' to form 'amount'
    int findMinCoins(vector<int> &coins, int cur, int amount, vector<vector<int>> &dp)
    {
        if (amount == 0)
            return 0;

        if (cur >= coins.size())
            return INT_MAX - 1;

        if (dp[cur][amount] != -1)
            return dp[cur][amount];

        int pickCurrent = INT_MAX;

        if (coins[cur] <= amount)
        {
            // Option 1: Take current coin and stay at same index
            pickCurrent = 1 + findMinCoins(coins, cur, amount - coins[cur], dp);
        }

        // Option 2: Skip current coin and move to next
        int skipCurrent = findMinCoins(coins, cur + 1, amount, dp);

        return dp[cur][amount] = min(pickCurrent, skipCurrent);
    }

    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
        int result = findMinCoins(coins, 0, amount, dp);
        return (result == INT_MAX - 1) ? -1 : result;
    }
};

/*
Approach:
- At each index, we decide to either:
    - Pick the current coin (if it fits) and reduce the amount.
    - Or skip the coin and move to the next one.
- Use top-down recursion with memoization (2D DP).

Time Complexity: O(N * A), where N = number of coins, A = amount
Space Complexity: O(N * A), for memoization table
*/


//===============================================================================================================================

// Recursion + Memoization ( 1D DP )

class Solution {
public:
    // Recursive DP with memoization to find min coins to make 'amt'
    int solve(int amt, vector<int> &coins, vector<int> &dp)
    {
        if (amt == 0)
            return 0;

        if (dp[amt] != -1)
            return dp[amt];

        int minCoins = INT_MAX;

        for (int coin : coins)
        {
            if (amt - coin >= 0)
            {
                int subRes = solve(amt - coin, coins, dp);
                if (subRes != INT_MAX)
                {
                    minCoins = min(minCoins, 1 + subRes);
                }
            }
        }

        return dp[amt] = minCoins;
    }

    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, -1);  // dp[i] = min coins to form i
        int result = solve(amount, coins, dp);
        return (result == INT_MAX) ? -1 : result;
    }
};

/*
Approach:
- Top-down recursion with memoization using 1D dp.
- Try every coin, and recursively compute the answer for (amount - coin).
- Memoize the result for each amount to avoid recomputation.

Time Complexity: O(N * A), where N = number of coins, A = amount
Space Complexity: O(A), for memoization array and recursion stack
*/



