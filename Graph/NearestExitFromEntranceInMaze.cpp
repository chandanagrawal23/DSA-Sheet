class Solution
{
public:
    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        int rows = maze.size();
        int cols = maze[0].size();
        int startX = entrance[0];
        int startY = entrance[1];

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int, int>> q;

        // Start from entrance
        q.push({startX, startY});
        visited[startX][startY] = true;

        int steps = 0;
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!q.empty())
        {
            int sz = q.size();

            while (sz--)
            {
                auto [x, y] = q.front();
                q.pop();

                // Check if it's an exit (not entrance and on border)
                if ((x != startX || y != startY) &&
                    (x == 0 || y == 0 || x == rows - 1 || y == cols - 1))
                {
                    return steps;
                }

                // Explore 4 directions
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                        !visited[nx][ny] && maze[nx][ny] == '.')
                    {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }

            ++steps;
        }

        return -1; // No exit reachable
    }
};

/*
Approach:
- We perform a Breadth-First Search (BFS) starting from the entrance point.
- At each level (step), we explore all four possible directions (up, down, left, right).
- If during BFS we encounter a boundary cell (excluding entrance) with '.', we return the number of steps taken so far — this guarantees the nearest exit due to BFS nature.
- We use a visited matrix to avoid revisiting cells.

Time Complexity: O(m × n)
- Each cell is visited at most once.

Space Complexity: O(m × n)
- For the visited matrix and BFS queue.
*/
