class Solution 
{
public:
    int shortestPathAllKeys(vector<string>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int totalKeys = 0;

        // Queue stores: {x, y, keyMask}
        queue<array<int, 3>> q;

        // 3D visited array: visited[row][col][keyMask]
        // There are at most 6 keys ⇒ 2^6 = 64 combinations
        vector<vector<vector<int>>> visited(rows, vector<vector<int>>(cols, vector<int>(64, 0)));

        // Step 1: Find starting point and count total keys
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                char ch = grid[i][j];
                if (ch == '@') 
                {
                    q.push({i, j, 0});  // starting position with 0 keys
                    visited[i][j][0] = 1;
                } 
                else if (ch >= 'a' && ch <= 'f') 
                {
                    totalKeys++;
                }
            }
        }

        vector<int> dx = {0, 1, 0, -1}; // right, down, left, up
        vector<int> dy = {1, 0, -1, 0};

        int steps = 0;

        // BFS
        while (!q.empty()) 
        {
            int size = q.size();
            while (size--) 
            {
                auto [x, y, keyMask] = q.front();
                q.pop();

                // If we have collected all keys, return the steps
                if (keyMask == (1 << totalKeys) - 1)
                    return steps;

                // Explore all 4 directions
                for (int dir = 0; dir < 4; ++dir) 
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    int newMask = keyMask;

                    // Skip if out of bounds or hitting a wall
                    if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] == '#')
                        continue;

                    char cell = grid[nx][ny];

                    // If it's a key, update bitmask
                    if (cell >= 'a' && cell <= 'f') 
                        newMask |= (1 << (cell - 'a'));

                    // If it's a lock and we don't have the key, skip
                    if (cell >= 'A' && cell <= 'F' && !(newMask & (1 << (cell - 'A'))))
                        continue;

                    // Only visit this state if it's not visited
                    if (!visited[nx][ny][newMask]) 
                    {
                        visited[nx][ny][newMask] = 1;
                        q.push({nx, ny, newMask});
                    }
                }
            }
            steps++;
        }

        // Not possible to collect all keys
        return -1;
    }
};

/*

 APPROACH:
------------
- Use BFS with state = {x, y, keyMask}
  → keyMask is a 6-bit number where each bit denotes if a key 'a' to 'f' is collected.
- We move in 4 directions and:
  → Collect keys (update keyMask).
  → Pass through locks only if the corresponding key is present.
  → Track visited states using a 3D array [row][col][keyMask].

 TERMINATION:
- When keyMask == (1 << totalKeys) - 1 (i.e., all keys are collected)

 TIME COMPLEXITY:
-------------------
- O(N * M * 2^K), where:
  → N × M = grid size
  → K = number of keys (≤ 6 ⇒ 64 states)
  → Each state is visited only once.

 SPACE COMPLEXITY:
--------------------
- O(N * M * 2^K) for visited array and queue.

Example:
grid = ["@.a.#", "###.#", "b.A.B"]
Answer = 8

*/
