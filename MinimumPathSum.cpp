// 1. Recursive + Memoization (Top-Down)
/*
Short approach: 
- Recursively explore right and down moves from (0,0).
- Use memo table to avoid recomputation.
- Return current cell value + min path sum of right/down.
- Time: O(m*n), Space: O(m*n)
*/
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        return dfs(grid, 0, 0, memo);
    }

private:
    int dfs(const vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
        int m = grid.size();
        int n = grid[0].size();

        if (i >= m || j >= n) return 1e9; // Out of bounds
        if (i == m - 1 && j == n - 1) return grid[i][j]; // Destination

        if (memo[i][j] != -1) return memo[i][j]; // Memoized result

        int right = dfs(grid, i, j + 1, memo);
        int down = dfs(grid, i + 1, j, memo);

        return memo[i][j] = grid[i][j] + min(right, down);
    }
};

//================================================================================================

// 2. Tabulation (Bottom-Up)
/*
Short approach:
- Build dp table from top-left to bottom-right.
- dp[i][j] = current cell + min(dp from top, dp from left).
- Initialize first row and column since moves are restricted.
- Time: O(m*n), Space: O(m*n)
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];

       // for first row
        for (int i = 1; i < m; i++) 
            dp[i][0] = dp[i-1][0] + grid[i][0];
      // for first col
        for (int j = 1; j < n; j++) 
            dp[0][j] = dp[0][j-1] + grid[0][j];

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }

        return dp[m-1][n-1];
    }
};

//================================================================================================

// 3. Space-Optimized Tabulation
/*
Short approach:
- Use 1D dp array to save space.
- dp[j] stores min path sum to cell in current row and column j.
- Update dp using dp[j] (previous row) and dp[j-1] (left in current row).
- Time: O(m*n), Space: O(n)
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> dp(n, 0);
        dp[0] = grid[0][0];

        for (int j = 1; j < n; j++) dp[j] = dp[j-1] + grid[0][j];

        for (int i = 1; i < m; i++) {
            dp[0] += grid[i][0];  // First column (only down moves)
            for (int j = 1; j < n; j++) {
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }

        return dp[n-1];
    }
};
