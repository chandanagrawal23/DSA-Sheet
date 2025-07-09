class Solution 
{
public:
    int minimumTime(vector<vector<int>>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();

        // If both immediate neighbors from (0, 0) are blocked for initial step, return -1
        if (grid[0][1] > 1 && grid[1][0] > 1) 
        {
            return -1;
        }

        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Min-heap priority queue: {time, row, col}
        priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
        pq.push({0, 0, 0}); // Start at (0,0) at time 0

        while (!pq.empty()) 
        {
            auto cur = pq.top();
            pq.pop();

            int time = cur[0];
            int r = cur[1];
            int c = cur[2];

            if (r == m - 1 && c == n - 1) 
            {
                return time;
            }

            if (visited[r][c]) 
            {
                continue;
            }

            visited[r][c] = true;

            for (const auto& dir : directions) 
            {
                int nr = r + dir[0];
                int nc = c + dir[1];

                // Skip out-of-bounds or visited cells
                if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc]) 
                {
                    continue;
                }

                // If arrival time is even and cell unlock time is same parity, you must wait an extra second
                bool mustWait = (grid[nr][nc] - time) % 2 == 0;
                int nextTime = max(grid[nr][nc] + mustWait, time + 1);

                pq.push({nextTime, nr, nc});
            }
        }

        return -1; // Destination not reachable
    }
};

/*
Approach:

- Each move takes 1 second and you can only enter cell (r, c) at time >= grid[r][c].
- If you arrive exactly at grid[r][c] and both have the same parity (e.g., even time to even cell), you’ll be blocked.
- So, in such a case, you must wait an extra second (odd/even flip).
- Use Dijkstra’s algorithm (min-heap) to explore the least time-cost path first.
- Early check: if both (0,1) and (1,0) are blocked for t=1, return -1 immediately.

Time Complexity:  O(m * n * log(m * n))
  - Each cell is processed once in the heap.

Space Complexity: O(m * n)
  - For visited array and heap.
*/
