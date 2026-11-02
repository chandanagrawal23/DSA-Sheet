
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<array<int, 2>> dirs = 
        {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        // Step 1: Multi-source BFS from all thieves to find the minimum distance to other cells
        queue<array<int, 2>> q;

        for (int i = 0; i < m; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (grid[i][j] == 1)
                    q.push({i, j});
            }
        }

        while (!q.empty()) 
        {
            auto [r, c] = q.front();
            q.pop();

            for (auto [dr, dc] : dirs) 
            {
                int nr = r + dr, nc = c + dc;

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 0) 
                {
                    grid[nr][nc] = grid[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Maximum Safeness Path using Max-Heap, but ham track minimum krenge , or minimum's ke max dekhenge
        priority_queue<array<int, 3>> pq;
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        pq.push({grid[0][0], 0, 0});
        vis[0][0] = true;

        while (!pq.empty()) 
        {
            auto [safe, r, c] = pq.top();
            pq.pop();

            if (r == m - 1 && c == n - 1)
                return safe - 1;

            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !vis[nr][nc]) 
                {

                    int newSafe = min(safe, grid[nr][nc]);
                    pq.push({newSafe, nr, nc});
                    vis[nr][nc] = true;
                }
            }
        }

        return -1;
    }
};

/*
Approach: Multi-Source BFS + Modified Dijkstra (Maximum Bottleneck Path)

1. Multi-Source BFS:
   Calculate the minimum distance of every cell from the nearest thief.
   Store distances in the grid itself.

2. Modified Dijkstra:
   Use a Max-Heap to maximize the minimum safeness factor
   along the path from (0,0) to (m-1,n-1).

   Transition:
   newSafe = min(currentSafe, grid[nr][nc])

   Return safe - 1 because BFS stores distance + 1
   to distinguish unvisited cells from thieves.

Time Complexity:  O(m * n * log(m * n))
Space Complexity: O(m * n)
*/
