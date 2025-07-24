class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    void wallsAndGates(vector<vector<int>> &rooms)
    {
        int m = rooms.size();
        int n = rooms[0].size();
        queue<pair<int, int>> q;

        // Step 1: Push all gates (value == 0) into queue
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (rooms[i][j] == 0)
                {
                    q.push({i, j});
                }
            }
        }

        // Step 2: Multi-source BFS from all gates
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : DIR)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Check if it's a valid room that has not been updated yet
                if (nx >= 0 && ny >= 0 && nx < m && ny < n && rooms[nx][ny] == INT_MAX)
                {
                    rooms[nx][ny] = rooms[x][y] + 1; // Set distance from nearest gate
                    q.push({nx, ny});
                }
            }
        }
    }
};

/*
Approach:

- Problem: Fill each empty room (INT_MAX) with distance to the nearest gate (0).
- Wall = -1, should be ignored.
- Use "multi-source BFS": start from all gates at once.

Steps:
1. Push all gates into a queue.
2. From each gate, perform BFS to fill nearby empty rooms with increasing distance.

Time Complexity: O(m * n)
- Each cell is visited once at most.

Space Complexity: O(m * n)
- For BFS queue in worst case (all cells empty).
*/
