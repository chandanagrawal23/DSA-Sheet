class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // DFS to mark the first island
    void dfs(int i, int j, vector<vector<int>> &grid, vector<vector<bool>> &visited, queue<pair<int, int>> &q, int n)
    {
        if (i < 0 || j < 0 || i >= n || j >= n || visited[i][j] || grid[i][j] == 0)
            return;

        visited[i][j] = true;
        q.push({i, j});

        for (auto [dx, dy] : DIR)
        {
            dfs(i + dx, j + dy, grid, visited, q, n);
        }
    }

    // BFS to expand to the second island
    int bfs(queue<pair<int, int>> &q, vector<vector<int>> &grid, vector<vector<bool>> &visited, int n)
    {
        int steps = 0;
        while (!q.empty())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [x, y] = q.front();
                q.pop();

                for (auto [dx, dy] : DIR)
                {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < n && ny < n && !visited[nx][ny])
                    {
                        if (grid[nx][ny] == 1)
                            return steps; // Found the second island

                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            ++steps;
        }
        return -1;
    }

    int shortestBridge(vector<vector<int>> &grid)
    {
        int n = grid.size();
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        bool found = false;

        // Find the first island and mark all its 1's via DFS
        for (int i = 0; i < n && !found; ++i)
        {
            for (int j = 0; j < n && !found; ++j)
            {
                if (grid[i][j] == 1)
                {
                    dfs(i, j, grid, visited, q, n);
                    found = true;
                }
            }
        }

        return bfs(q, grid, visited, n);
    }
};

/*
Approach (DFS + BFS):

1. "Identify and mark the first island:"
   - Use DFS to mark all cells (1s) of the first island as visited.
   - Push all its boundary coordinates into a queue.

2. "BFS to expand towards the second island:"
   - Start from all positions in the first island (in the queue).
   - At each BFS level, flip zeros outward.
   - The moment we reach a cell that is part of the second island (grid[i][j] == 1 and unvisited), return the steps taken.

"Time Complexity:" O(N^2)  
- DFS + BFS visit every cell at most once.

"Space Complexity:" O(N^2)  
- For visited array and queue.

Example Trace (grid = [[0,1,0],[0,0,0],[0,0,1]]):
- DFS marks the top-left island starting at (0,1)
- Queue initialized with island 1 boundary → BFS starts expanding
- After 2 steps, reaches (2,2), the start of island 2 → returns 2
*/
