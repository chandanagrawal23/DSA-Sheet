// 1. Recursion + Memoization (Top-Down DP)

/*
-------------------  Short approach  -------------------
Treat each cell (r,c) as a state.  A DFS explores “Down” and “Right” moves.
Cache every state in a memo table so each is solved once.
Time  O(m·n),  Space  O(m·n) for memo  +  O(m+n) recursion stack.
*/

class Solution
{
public:
    int uniquePaths(int rows, int cols)
    {
        vector<vector<int>> memo(rows, vector<int>(cols, -1));
        return dfs(0, 0, rows, cols, memo);
    }

private:
    int dfs(int r, int c, int rows, int cols, vector<vector<int>> &memo)
    {
        if (r == rows - 1 && c == cols - 1)
        {
            return 1;                      // reached destination
        }

        if (r >= rows || c >= cols)
        {
            return 0;                      // outside grid
        }

        if (memo[r][c] != -1)
        {
            return memo[r][c];             // cached
        }

        int down  = dfs(r + 1, c, rows, cols, memo);
        int right = dfs(r, c + 1, rows, cols, memo);
        memo[r][c] = down + right;
        return memo[r][c];
    }
};

// =====================================================================================================================================================

//2. Bottom-Up DP (Full 2-D Table)

/*
-------------------  Short approach  -------------------
dp[r][c] = (# paths from above) + (# paths from left).
First row and first column stay 1 (only one straight path).
Time  O(m·n),  Space  O(m·n).
*/


class Solution
{
public:
    int uniquePaths(int rows, int cols)
    {
        vector<vector<int>> dp(rows, vector<int>(cols, 1));   // first row/col = 1

        for (int r = 1; r < rows; r++)
        {
            for (int c = 1; c < cols; c++)
            {
                dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
            }
        }
        return dp[rows - 1][cols - 1];
    }
};

// =====================================================================================================================================================

//3. Bottom-Up DP with 1-D Rolling Array (Space O(n))

/*
-------------------  Short approach  -------------------
Reuse one row: update left-to-right so dp[c] still holds “above” while dp[c-1] is “left”.
Time  O(m·n),  Space  O(n).
*/

class Solution
{
public:
    int uniquePaths(int rows, int cols)
    {
        vector<int> dp(cols, 1);           // row 0 is all 1s
        for (int r = 1; r < rows; r++)
        {
            for (int c = 1; c < cols; c++)
            {
                dp[c] += dp[c - 1];        // current ← above (dp[c]) + left (dp[c-1])
            }
        }
        return dp[cols - 1];
    }
};


// =====================================================================================================================================================


//4. Combinatorics (Direct Formula, Space O(1))

/*
-------------------  Short approach  -------------------
A path is a sequence of (m-1) Downs and (n-1) Rights.
Choose positions for either set:  C(m+n-2, m-1)  =  (m+n-2)! / ((m-1)!(n-1)!).
Compute iteratively to avoid overflow.
Time  O(min(m,n)),  Space  O(1).
*/
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        return combination(m + n - 2, min(m - 1, n - 1));
    }

private:
    int combination(int total, int pick)
    {
        long long res = 1;
        for (int i = 1; i <= pick; i+
        {
            res = res * (total - i + 1) / i;   // build C(total, pick) iteratively
        }
        return static_cast<int>(res);          // safe: problem guarantees ≤ 2 × 10⁹
    }
};




