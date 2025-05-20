class Solution {
public:
    // Helper function using recursion + memoization
    // wallIndex: current wall being considered
    // wallsLeft: number of walls left to paint
    int dpHelper(int wallIndex, int wallsLeft, vector<int>& cost, vector<int>& time, vector<vector<int>>& dp) {
        // Base case: All walls painted
        if (wallsLeft <= 0) return 0;

        // If no more walls to consider but still some left unpainted
        if (wallIndex >= cost.size()) return 1e9; // Infeasible

        // Check memoized result
        if (dp[wallIndex][wallsLeft] != -1) 
            return dp[wallIndex][wallsLeft];

        // ------------------------------------------
        // Option 1: Use the paid painter for this wall
        // - He paints 1 wall in time[wallIndex] units
        // - During that time, the free painter can paint `time[wallIndex]` other walls (1 per time unit)
        // - So total walls painted in parallel = 1 (paid) + time[wallIndex] (free)
        // - Reduce wallsLeft by (1 + time[wallIndex])
        // - Add cost of this paid wall
        // ------------------------------------------
        int usePaid = cost[wallIndex] + dpHelper(wallIndex + 1, wallsLeft - 1 - time[wallIndex], cost, time, dp);

        // ------------------------------------------
        // Option 2: Skip this wall (don't assign it to the paid painter now)
        // - This does NOT mean the free painter paints it
        // - Free painter can only work *while* paid painter paint --- IMPO
        // - So we keep the wallsLeft unchanged and move to the next wall
        // ------------------------------------------
        int skipPaid = dpHelper(wallIndex + 1, wallsLeft, cost, time, dp);

        // Store and return the minimum cost between the two options
        return dp[wallIndex][wallsLeft] = min(usePaid, skipPaid);
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();

        // dp[i][j] stores the minimum cost to paint j walls starting from index i
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        // Start from index 0 with all n walls needing to be painted
        return dpHelper(0, n, cost, time, dp);
    }
};
