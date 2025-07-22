class Solution
{
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};

    // Perform BFS to explore connected farmland and return the top-left and bottom-right corners
    vector<int> bfs(int i, int j, vector<vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        pair<int, int> topLeft = {i, j}, bottomRight = {i, j};
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = 0; // Mark visited

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            // Update the bottom-right boundary as we explore
            bottomRight = {max(bottomRight.first, x), max(bottomRight.second, y)};

            // Explore 4-directionally
            for (int d = 0; d < 4; ++d)
            {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 1)
                {
                    grid[nx][ny] = 0; // Mark visited
                    q.push({nx, ny});
                }
            }
        }

        return {topLeft.first, topLeft.second, bottomRight.first, bottomRight.second};
    }

public:
    vector<vector<int>> findFarmland(vector<vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> result;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // If farmland found and not yet visited
                if (grid[i][j] == 1)
                {
                    result.push_back(bfs(i, j, grid)); // Capture rectangle bounds
                }
            }
        }

        return result;
    }
};

/*
Approach:
- For each unvisited farmland cell (value 1), trigger a BFS to find the full connected farmland group.
- BFS marks all visited cells (sets them to 0) and keeps track of the bounding top-left and bottom-right corners.
- These corners are returned as the rectangle representing the farmland group.

Time Complexity: O(m × n)
- Each cell is visited at most once.

Space Complexity: O(m × n)
- BFS queue can hold all farmland cells in a worst-case scenario.
*/
