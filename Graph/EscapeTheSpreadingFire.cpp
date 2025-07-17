/*
=========================
Key Rule from Problem:  |
=========================

"Even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse."

This is only true for the destination cell.

So what does this mean in code?
1) For all intermediate cells: you can only step into them before the fire arrives:
            nextTime < fireArrivalTime[nextX][nextY]

2) For the destination (safehouse) only: you're allowed to enter at the exact same time as the fire:
            nextTime <= fireArrivalTime[nextX][nextY]

*/
class Solution
{
public:
    int maximumMinutes(vector<vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        int INF = 1e9;

        // fire[i][j] stores the earliest time fire reaches cell (i, j)
        vector<vector<int>> fire(m, vector<int>(n, INF));
        queue<pair<int, int>> q;

        // 1. Multi-source BFS to compute fire arrival time from all sources
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)  // fire source
                {
                    fire[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty())
        {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : dirs)
            {
                int nx = x + dx, ny = y + dy;

                // fire spreads to adjacent empty cells
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    grid[nx][ny] == 0 && fire[nx][ny] == INF)
                {
                    fire[nx][ny] = fire[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // 2. Binary Search the maximum wait time at starting cell
        int left = 0, right = m * n, ans = -1;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (can_escape(mid, fire, grid, m, n, dirs))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        // If fire never blocks destination, we can wait indefinitely
        return (ans == m * n) ? INF : ans;
    }

    bool can_escape(int initialWaitTime, vector<vector<int>>& fireArrivalTime, vector<vector<int>>& grid, int rows, int cols, vector<pair<int, int>>& directions)
    {
        // Can't wait if fire reaches start cell before or at wait time
        if (initialWaitTime >= fireArrivalTime[0][0])
            return false;

        queue<array<int, 3>> q;  // {x, y, current time}
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        q.push({0, 0, initialWaitTime});
        visited[0][0] = true;

        while (!q.empty())
        {
            auto cell = q.front(); q.pop();
            int currX = cell[0], currY = cell[1], currTime = cell[2];

            // Reached the destination
            if (currX == rows - 1 && currY == cols - 1)
                return true;

            for (auto [dx, dy] : directions)
            {
                int nextX = currX + dx;
                int nextY = currY + dy;
                int nextTime = currTime + 1;

                // Check boundary and block make sure , next cell is grass and not yet visited.
                if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols &&
                    grid[nextX][nextY] == 0 && !visited[nextX][nextY])
                {
                    // Safe to go if fire arrives after we pass
                    // Or we arrive exactly when fire does but it's the destination
                    // read question again : Note that even if the fire spreads to the safehouse immediately after you have reached it, 
                    //                       it will be counted as safely reaching the safehouse.
                    if (nextTime < fireArrivalTime[nextX][nextY] || 
                        (nextX == rows - 1 && nextY == cols - 1 && nextTime <= fireArrivalTime[nextX][nextY]))
                    {
                        visited[nextX][nextY] = true;
                        q.push({nextX, nextY, nextTime});
                    }
                }
            }
        }
        return false;  // No valid path found
    }
};

/*
Approach Explained
====================
Fire Spread BFS:
  Multi-source BFS from all fire cells to calculate when fire reaches each cell (fire[x][y] = time).
  Blocked cells (grid[x][y] == 2) are not traversable for fire or humans.
  
Binary Search on Wait Time:
  Try waiting mid minutes at the start (0,0), and then simulate a BFS path.
  If you can safely reach the destination with that wait, try a longer wait.
  Else try a shorter wait.
  Edge case: if fire never blocks you even after m*n minutes, return a large number (1e9).

Escape Simulation (can_escape):
  Normal BFS from (0,0) starting at initialWaitTime.
  Ensure fire hasn't reached the cell before or when you arrive.
  Special case: at destination cell, reaching at the same time as fire is allowed.

** Time Complexity
    Fire BFS: O(m * n)
    Binary Search Loop: log(m * n) iterations
    Escape BFS per iteration: O(m * n)

    Total: O((m * n) * log(m * n))

** Space Complexity
    Fire matrix + visited matrix: O(m * n)
    BFS queues: up to O(m * n)

    Total: O(m * n)

*/
