class Solution
{
public:
    int latestDayToCross(int rows , int cols, vector<vector<int>> &cells)
    {
        vector<vector<int>> grid(rows, vector<int>(cols, 0));
        int latestDay = 0;
        int low = 0, high = cells.size() - 1;

        // Binary search to find the latest possible day to cross
        while (low <= high)
        {
            int mid = (low + high) / 2;

            // Flood the grid for the first 'mid' days
            for (int i = 0; i < mid; i++)
            {
                int r = cells[i][0] - 1;
                int c = cells[i][1] - 1;

                grid[r][c] = 1;
            }

            // Check if it's still possible to reach the last row
            if (canReachBottom(grid, rows, cols))
            {
                latestDay = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }

            // Reset flooded cells for next iteration
            for (int i = 0; i < mid; i++)
            {
                int r = cells[i][0] - 1;
                int c = cells[i][1] - 1;

                 grid[r][c] = 0;
            }
        }

        return latestDay;
    }

    // BFS to check if we can reach the bottom row from the top row , see we are not passing by &, we are passing by value
    bool canReachBottom(vector<vector<int>> grid, int rows, int cols)
    {
        // Direction vectors: left, right, up, down
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};
        queue<pair<int, int>> q;

        // Start from all unblocked cells in the top row
        for (int col = 0; col < cols; col++)
        {
            if (grid[0][col] == 0)
            {
                q.push({0, col});
                grid[0][col] = 1; // mark visited
            }
        }

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == rows - 1)
                return true;

            for (int dir = 0; dir < 4; dir++)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // If within bounds and not flooded or visited
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0)
                {
                    q.push({nx, ny});
                    grid[nx][ny] = 1; // mark as visited
                }
            }
        }

        return false;
    }
};


/**
Approach:
- We're given a grid that floods cell by cell each day.
- We need to find the "latest day" we can still cross from top to bottom.
- Use "Binary search" on day index.
    - For a given day, mark the flooded cells.
    - Then use BFS to check if there's a path from the top to the bottom row.
    - If yes, try a later day. If no, try earlier.
- BFS only moves through unflooded (value 0) cells.

Time Complexity:
- O(log(D) * (R * C)), where D = days = cells.size()

Space Complexity:
- O(R * C) for grid and visited tracking
*/
