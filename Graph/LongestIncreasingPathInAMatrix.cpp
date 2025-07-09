class Solution 
{
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        int n = matrix.size();
        int m = matrix[0].size();

        // Directions: right, left, up, down
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {1, -1, 0, 0};

        map<pair<int, int>, vector<pair<int, int>>> adj;  // DAG adjacency list
        vector<vector<int>> indegree(n, vector<int>(m, 0));  // indegree for each cell

        // Step 1: Build the graph with edges from lower -> higher values
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                for (int d = 0; d < 4; d++) 
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    // Only move to strictly increasing neighbor
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && matrix[ni][nj] > matrix[i][j]) 
                    {
                        adj[{i, j}].push_back({ni, nj});
                        indegree[ni][nj]++;
                    }
                }
            }
        }

        // Step 2: Push all nodes with 0 indegree into the queue
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                if (indegree[i][j] == 0) 
                {
                    q.push({i, j});
                }
            }
        }

        // Step 3: Perform level-order BFS (Kahn's algorithm)
        int maxLength = 0;
        while (!q.empty()) 
        {
            int size = q.size();
            maxLength++;  // each level represents one more step in the path

            for (int k = 0; k < size; k++) 
            {
                auto [x, y] = q.front();
                q.pop();

                for (auto [nx, ny] : adj[{x, y}]) 
                {
                    indegree[nx][ny]--;
                    if (indegree[nx][ny] == 0) 
                    {
                        q.push({nx, ny});
                    }
                }
            }
        }

        return maxLength;
    }
};

/*
Approach:
---------
We treat the matrix as a **Directed Acyclic Graph (DAG)** where:
- Each cell is a node.
- There is a directed edge from cell (i, j) to (ni, nj) if matrix[ni][nj] > matrix[i][j].

This forms a DAG because we only go from smaller values to larger ones, preventing cycles.

We apply **Topological Sorting (Kahn’s Algorithm)** to this graph to find the **Longest Path**:
- Start BFS from all cells with 0 indegree (no smaller neighbor).
- In each BFS level, we move to next increasing neighbors.
- Number of BFS levels = length of longest increasing path.

This approach is efficient because:
- Each cell is processed only once.
- We avoid repeated DFS calls using memoization by level-wise BFS.

Time: O(m * n)
Space: O(m * n)
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Solution 
{
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        vector<vector<int>> dp(rows, vector<int>(cols, -1)); // Memo table
        int maxPath = 0;

        // Try DFS from every cell
        for (int row = 0; row < rows; row++) 
        {
            for (int col = 0; col < cols; col++) 
            {
                maxPath = max(maxPath, dfs(matrix, dp, row, col, -1));
            }
        }

        return maxPath;
    }

private:
    // DFS helper with memoization
    int dfs(vector<vector<int>>& mat, vector<vector<int>>& dp, int row, int col, int prevVal)
    {
        // Invalid move: out of bounds or not increasing
        if (row < 0 || row >= mat.size() || col < 0 || col >= mat[0].size() || mat[row][col] <= prevVal)
            return 0;

        if (dp[row][col] != -1)
            return dp[row][col]; // Already computed

        // Explore four directions
        int down  = dfs(mat, dp, row + 1, col, mat[row][col]);
        int up    = dfs(mat, dp, row - 1, col, mat[row][col]);
        int right = dfs(mat, dp, row, col + 1, mat[row][col]);
        int left  = dfs(mat, dp, row, col - 1, mat[row][col]);

        // Store result and return
        return dp[row][col] = 1 + max({down, up, right, left});
    }
};

/*
Approach:
---------
- From every cell, we try to move to neighbors with strictly increasing values.
- DFS is used to explore all valid paths from a cell, with memoization to avoid recomputation.
- For each (row, col), we store the max increasing path starting from there in dp[row][col].

Why DFS + Memoization:
-----------------------
- This is a DAG (Directed Acyclic Graph) problem where each node (cell) points to higher-valued neighbors.
- DFS explores all increasing paths, and memoization ensures O(1) reuse of computed subproblems.

Time Complexity: O(m * n)
- Each cell is visited once, and each direction is explored only once per cell.

Space Complexity: O(m * n)
- Used for dp table and recursion stack.
*/
