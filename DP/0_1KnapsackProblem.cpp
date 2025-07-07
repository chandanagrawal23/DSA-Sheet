#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
    // Recursive helper with memoization
    int knapsack(int index, int capacity, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp)
    {
        if (index == 0)
        {
            // If only one item left, take it if it fits
            return (wt[0] <= capacity) ? val[0] : 0;
        }

        if (dp[index][capacity] != -1)
        {
            return dp[index][capacity]; // Return cached result
        }

        // Option 1: skip the current item
        int notTake = knapsack(index - 1, capacity, wt, val, dp);

        // Option 2: take the item (if it fits)
        int take = 0;
        if (wt[index] <= capacity)
        {
            take = val[index] + knapsack(index - 1, capacity - wt[index], wt, val, dp);
        }

        // Memoize and return max of take or notTake
        return dp[index][capacity] = max(take, notTake);
    }

    int knapSack(int W, vector<int>& wt, vector<int>& val, int n)
    {
        // Initialize DP table with -1 (uncomputed)
        vector<vector<int>> dp(n, vector<int>(W + 1, -1));
        return knapsack(n - 1, W, wt, val, dp);
    }
};

int main() 
{
    Solution sol;

    // Example 1
    int W1 = 50;
    vector<int> wt1 = {10, 20, 30};   // Weights of items
    vector<int> val1 = {60, 100, 120}; // Corresponding values
    int n1 = wt1.size();               // Number of items

    cout << "Example 1: Maximum value = " << sol.knapSack(W1, wt1, val1, n1) << endl;
    // Expected Output: 220

    // Example 2
    int W2 = 8;
    vector<int> wt2 = {3, 4, 5};
    vector<int> val2 = {30, 50, 60};
    int n2 = wt2.size();

    cout << "Example 2: Maximum value = " << sol.knapSack(W2, wt2, val2, n2) << endl;
    // Expected Output: 90

    return 0;
}

/*
Approach:
- For each item, we either take it (if it fits) or skip it.
- Use recursion + memoization to avoid recomputing subproblems.
- Store results in a 2D dp table indexed by item and remaining capacity.

Time Complexity: O(n * W)
Space Complexity: O(n * W) for dp table
*/
