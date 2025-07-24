// DFS Based Approach
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) 
    {
        int n = grid1.size();        // number of rows
        int m = grid1[0].size();     // number of columns
        int subIslands = 0;

        // Step 1: Remove parts in grid2 that are land but not land in grid1
        // remove non common island from grid 2
        for (int row = 0; row < n; ++row) 
        {
            for (int col = 0; col < m; ++col) 
            {
                // If grid2 has land but grid1 doesn't => can't be part of a sub-island
                if (grid2[row][col] == 1 && grid1[row][col] == 0) 
                {
                    eraseIsland(grid2, row, col, n, m);
                }
            }
        }

        // Step 2: Count remaining islands in grid2
        for (int row = 0; row < n; ++row) 
        {
            for (int col = 0; col < m; ++col) 
            {
                if (grid2[row][col] == 1) 
                {
                    subIslands++;
                    eraseIsland(grid2, row, col, n, m);
                }
            }
        }

        return subIslands;
    }

private:
    // DFS to erase an island from grid2
    void eraseIsland(vector<vector<int>>& grid, int i, int j, int n, int m) 
    {
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1) 
        {
            return;
        }

        grid[i][j] = 0;  // mark visited

        // Recurse in all 4 directions
        eraseIsland(grid, i - 1, j, n, m);
        eraseIsland(grid, i + 1, j, n, m);
        eraseIsland(grid, i, j - 1, n, m);
        eraseIsland(grid, i, j + 1, n, m);
    }
};
/*
Approach:

1. An island in `grid2` is only valid if all its land cells (1)  are also land in `grid1`.

2. So, in Step 1: 
   - Remove all land in grid2 that lies over water in grid1, means in grid2 the cell is 1 , but in grid1 it is water (0)
   - These parts cannot be part of a valid sub-island.
   - We do this using DFS.

3. Step 2:
   - Now grid2 only contains valid sub-islands.
   - Count number of islands using standard DFS island counting.

Time Complexity: O(m * n)
- Every cell is visited at most once.

Space Complexity: O(m * n) worst case recursion stack
*/

//////////////////////////////////////////////////////////////////////////////////////////////
// BFS Based Approach
// BFS Based Approach
class Solution {
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) 
    {
        int n = grid1.size();        // number of rows
        int m = grid1[0].size();     // number of columns
        int subIslands = 0;

        // Step 1: Remove parts in grid2 that are land but not land in grid1
        // remove non common island from grid 2
        for (int row = 0; row < n; ++row) 
        {
            for (int col = 0; col < m; ++col) 
            {
                // If grid2 has land but grid1 doesn't => can't be part of a sub-island
                if (grid2[row][col] == 1 && grid1[row][col] == 0) 
                {
                    eraseIsland(grid2, row, col, n, m);
                }
            }
        }

        // Step 2: Count remaining islands in grid2
        for (int row = 0; row < n; ++row) 
        {
            for (int col = 0; col < m; ++col) 
            {
                if (grid2[row][col] == 1) 
                {
                    subIslands++;
                    eraseIsland(grid2, row, col, n, m);
                }
            }
        }

        return subIslands;
    }

private:
    // BFS to erase an island from grid2
    void eraseIsland(vector<vector<int>>& grid, int i, int j, int n, int m) 
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = 0; // mark visited

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : DIR)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == 1)
                {
                    grid[nx][ny] = 0; // mark visited or say make land->water
                    q.push({nx, ny});
                }
            }
        }
    }
};
