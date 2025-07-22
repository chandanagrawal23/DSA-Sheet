class Solution
{
public:
    int shortestPath(vector<vector<int>> &grid, int k)
    {
        int rows = grid.size(), cols = grid[0].size();

        // Queue stores: {x, y, steps, remaining_k}
        queue<array<int, 4>> q;
        q.push({0, 0, 0, k});

        // visited[x][y][k_remaining] = true if already visited
        vector<vector<vector<bool>>> vis(rows, vector<vector<bool>>(cols, vector<bool>(k + 1, false)));
        vis[0][0][k] = true;

        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        while (!q.empty())
        {
            auto [x, y, steps, remK] = q.front();
            q.pop();

            // Destination reached
            if (x == rows - 1 && y == cols - 1)
            {
                return steps;
            }

            for (int d = 0; d < 4; ++d)
            {
                int nx = x + dx[d];
                int ny = y + dy[d];
                int newK = remK;

                // Check bounds
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols)
                {
                    if (grid[nx][ny] == 1)
                    {
                        --newK; // obstacle consumed
                    }

                    if (newK >= 0 && !vis[nx][ny][newK])
                    {
                        vis[nx][ny][newK] = true;
                        q.push({nx, ny, steps + 1, newK});
                    }
                }
            }
        }

        return -1; // Not reachable
    }
};

/*
Approach:
- BFS is used to find the shortest path from (0,0) to (n-1,m-1) while optionally eliminating up to 'k' obstacles.
- At each step, we consider 4-directional moves and track the remaining quota for obstacle elimination.
- We use a 3D visited array to track states uniquely based on (x, y, remaining_k).

Time Complexity: O(m × n × k)
- Each state (cell + remaining eliminations) is visited at most once.

Space Complexity: O(m × n × k)
- Due to the 3D visited array and BFS queue.
*/
