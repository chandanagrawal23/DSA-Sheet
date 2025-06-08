class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();

        // Two DP tables: best (max) and worst (min) product that can reach (i,j)
        vector<vector<long long>> maxDp(m, vector<long long>(n));
        vector<vector<long long>> minDp(m, vector<long long>(n));

        maxDp[0][0] = minDp[0][0] = grid[0][0];

        // Initialize first column
        for (int i = 1; i < m; ++i) 
        {
            maxDp[i][0] = maxDp[i-1][0] * grid[i][0];
            minDp[i][0] = maxDp[i-1][0] * grid[i][0];
        }
        // Initialize first row
        for (int j = 1; j < n; ++j)
        {
            maxDp[0][j] = maxDp[0][j-1] * grid[0][j];
            minDp[0][j] = maxDp[0][j-1] * grid[0][j];
        }

        // Fill dp arrays
        for (int i = 1; i < m; ++i) 
        {
            for (int j = 1; j < n; ++j) 
            {
                long long val = grid[i][j];

                long long maxFromTop = maxDp[i-1][j] * val;
                long long minFromTop = minDp[i-1][j] * val;
                long long maxFromLeft = maxDp[i][j-1] * val;
                long long minFromLeft = minDp[i][j-1] * val;

                maxDp[i][j] = max({maxFromTop, minFromTop, maxFromLeft, minFromLeft});
                minDp[i][j] = min({maxFromTop, minFromTop, maxFromLeft, minFromLeft});
            }
        }

        long long ans = maxDp[m-1][n-1];
        if (ans < 0) 
            return -1;

        return ans % MOD;
    }
};

/* ------------------------------------------------------------------------
   Short approach
   1. Keep two DP tables:
        • maxDp[i][j] – max product reaching (i,j)
        • minDp[i][j] – min product reaching (i,j)
   2. For each cell, consider products coming from top and left, multiplied
      by the current cell value.  Because a negative value can turn a minimum
      into a new maximum (and vice-versa), we update both tables with all
      four possibilities.
   3. After filling the grid, maxDp[m-1][n-1] is the largest achievable
      product.  If it is negative, return –1; otherwise return it modulo
      1 000 000 007.
   --------------------------------------------------------------------
   Time   : O(m · n)  — each cell processed once.
   Space  : O(m · n)  — two auxiliary DP grids of the same size.
   -------------------------------------------------------------------- */
