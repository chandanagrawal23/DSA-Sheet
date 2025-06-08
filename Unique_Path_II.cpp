// 1. Recursion + Memoization (Top-Down DP)

/*
-------------------  Short approach  -------------------
DFS from (0,0); an obstacle or boundary returns 0.  
Cache every (r,c) in `memo` so each sub-problem is solved once.  
Time  O(m·n)   |   Space  O(m·n) memo  +  O(m+n) recursion stack.
*/

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &grid)
    {
        const int rows = grid.size();
        const int cols = grid[0].size();

        if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1)
        {
            return 0;                       // start or target blocked
        }

        vector<vector<int>> memo(rows, vector<int>(cols, -1));
        return dfs(0, 0, rows, cols, grid, memo);
    }

private:
    int dfs(int r,
            int c,
            int rows,
            int cols,
            const vector<vector<int>> &grid,
            vector<vector<int>> &memo)
    {
        if (r == rows || c == cols || grid[r][c] == 1)
        {
            return 0;                       // out of bounds or obstacle
        }

        if (r == rows - 1 && c == cols - 1)
        {
            return 1;                       // reached target
        }

        if (memo[r][c] != -1)
        {
            return memo[r][c];
        }

        int down  = dfs(r + 1, c, rows, cols, grid, memo);
        int right = dfs(r, c + 1, rows, cols, grid, memo);

        memo[r][c] = down + right;
        return memo[r][c];
    }
};


//=========================================================================================================================
//2. ✦ Bottom-Up DP (Full 2-D Table)

/*
-------------------  Short approach  -------------------
1. Initialize first row and column with 1s unless an obstacle is found (then break).
2. For all other cells:
   - If cell is free, add paths from top and left.
   - If cell is an obstacle, set dp[i][j] = 0.
3. Final answer is dp[m-1][n-1].
Time  O(m·n),  Space  O(m·n)
*/

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &a)
    {
        int m = a.size();
        int n = a[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Fill first row
        for (int j = 0; j < n; j++)
        {
            if (a[0][j] == 0)
            {
                dp[0][j] = 1;
            }
            else
            {
                break;  // obstacle found, rest of the row stays 0
            }
        }

        // Fill first column
        for (int i = 0; i < m; i++)
        {
            if (a[i][0] == 0)
            {
                dp[i][0] = 1;
            }
            else
            {
                break;  // obstacle found, rest of the column stays 0
            }
        }

        // Fill the rest of the DP table
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (a[i][j] == 0)
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
                else
                {
                    dp[i][j] = 0; // obstacle
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};


