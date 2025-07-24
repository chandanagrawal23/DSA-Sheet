// DFS Based Approach, Note, here , Water is 1 , and land is 0 

class Solution
{
public:
    void dfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();

        // Out of bounds or water
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 1)
            return;

        grid[i][j] = 1; // mark visited (turn 0 -> 1) , make water

        dfs(grid, i + 1, j); // down
        dfs(grid, i - 1, j); // up
        dfs(grid, i, j + 1); // right
        dfs(grid, i, j - 1); // left
    }

    int closedIsland(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        // Step 1: Remove all land connected to boundary (cannot be closed islands)
        for (int i = 0; i < m; ++i)
        {
            if (grid[i][0] == 0)
                dfs(grid, i, 0);
            if (grid[i][n - 1] == 0)
                dfs(grid, i, n - 1);
        }

        for (int j = 0; j < n; ++j)
        {
            if (grid[0][j] == 0)
                dfs(grid, 0, j);
            if (grid[m - 1][j] == 0)
                dfs(grid, m - 1, j);
        }

        // Step 2: Count the remaining isolated 0-groups (closed islands)
        int closedIslands = 0;

        for (int i = 1; i < m - 1; ++i)
        {
            for (int j = 1; j < n - 1; ++j)
            {
                if (grid[i][j] == 0)
                {
                    dfs(grid, i, j);
                    closedIslands++;
                }
            }
        }

        return closedIslands;
    }
};

/*
Approach:

1. Any island (group of 0s) touching the grid boundary is NOT closed.
   So we first remove all such islands by doing DFS from boundary 0s and marking them visited (turn to 1s).

2. Then, we iterate the inner grid (excluding borders), and for every unvisited 0,
   we start a DFS to explore the full island and count it as a closed island.

3. For each island visited in this step, we increment the count.

Time Complexity: O(m * n)
- We visit each cell at most once.

Space Complexity: O(m * n) in worst case (DFS recursion stack)
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// BFS Based Approach
class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    void bfs(vector<vector<int>> &grid, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = 1; // mark visited

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : DIR)
            {
                int ni = x + dx;
                int nj = y + dy;

                if (ni >= 0 && nj >= 0 && ni < m && nj < n && grid[ni][nj] == 0)
                {
                    grid[ni][nj] = 1; // make water 
                    q.push({ni, nj});
                }
            }
        }
    }

    int closedIsland(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        // Step 1: Remove all 0s(land) connected to border (cannot be closed)
        for (int i = 0; i < m; ++i)
        {
            if (grid[i][0] == 0)
                bfs(grid, i, 0);
            if (grid[i][n - 1] == 0)
                bfs(grid, i, n - 1);
        }

        for (int j = 0; j < n; ++j)
        {
            if (grid[0][j] == 0)
                bfs(grid, 0, j);
            if (grid[m - 1][j] == 0)
                bfs(grid, m - 1, j);
        }

        // Step 2: Count remaining closed islands
        int closedIslands = 0;

        for (int i = 1; i < m - 1; ++i)
        {
            for (int j = 1; j < n - 1; ++j)
            {
                if (grid[i][j] == 0)
                {
                    bfs(grid, i, j);
                    closedIslands++;
                }
            }
        }

        return closedIslands;
    }
};

/*
Approach (BFS):

1. Any 0 that touches the border cannot be part of a closed island.
   → Run BFS from all boundary 0s to mark them as visited (set to 1).

2. Now iterate the grid (excluding boundary),
   and every time we find a 0, it is a closed island.
   → Run BFS to mark the entire island and increment count.

Time Complexity: O(m * n)
- Each cell visited once.

Space Complexity: O(m * n)
- For BFS queue in worst case.
*/
