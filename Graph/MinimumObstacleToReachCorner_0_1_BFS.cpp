class Solution 
{
public:
    int minimumObstacles(vector<vector<int>>& grid) 
    {
        // Direction vectors: down, up, right, left
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
      
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> minCost(m, vector<int>(n, INT_MAX));
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        deque<pair<int, int>> dq;
        dq.push_front({0, 0});
        minCost[0][0] = 0;

        while (!dq.empty()) 
        {
            auto [x, y] = dq.front();
            dq.pop_front();

            for (int dir = 0; dir < 4; dir++) 
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) 
                {
                    // Cost to enter the next cell: 0 (free) or 1 (obstacle)
                    minCost[nx][ny] = minCost[x][y] + grid[nx][ny];

                    // If obstacle, push to back (cost 1); else to front (cost 0)
                    if (grid[nx][ny] == 1) 
                    {
                        dq.push_back({nx, ny});
                    } 
                    else 
                    {
                        dq.push_front({nx, ny});
                    }

                    visited[nx][ny] = true;
                }
            }
        }

        return minCost[m - 1][n - 1];
    }
};

/*
Approach:

We apply 0-1 BFS using a deque:
- Use deque to always expand the lowest-cost path first.
- Free cells (grid value = 0) are explored with priority by pushing to the front.
- Obstacle cells (grid value = 1) are explored with delay by pushing to the back.
- We mark visited cells to avoid redundant processing.

Time Complexity:  O(m * n)
Each cell is processed once and has up to 4 neighbors.

Space Complexity: O(m * n)
We use additional 2D vectors for cost and visited tracking.
*/
