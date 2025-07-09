/*
🧩 Problem: Minimum Magic Path Cost

You are given a 2D grid of size m x n. Each cell contains a magic cost between 0 and 3.

From any cell (i, j), you can move to one of its 4 neighbors (up, down, left, right) if within bounds.

Each move costs the **magic value of the destination cell**.

Your task is to find the minimum total cost to reach the bottom-right cell (m-1, n-1) from the top-left cell (0, 0).

🔸 Constraints:
- 1 <= m, n <= 500
- 0 <= grid[i][j] <= 3

🔹 Input:
grid = [
  [0, 1, 2],
  [3, 2, 1],
  [0, 1, 0]
]

🔹 Output:
2

🔹 Explanation:
(0,0) → (1,1) → (2,2) = 0 + 2 + 0 = ✅ 2 (minimum total cost)
*/

class Solution 
{
public:
    int minMagicPath(vector<vector<int>>& grid) 
    {
        int m = grid.size(), n = grid[0].size();

        // Distance matrix initialized with INF
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 0;

        // Max magic value is 3, so 0–3 BFS → use 4 buckets
        const int MAX_COST = 3;
        vector<deque<pair<int, int>>> buckets(MAX_COST + 1);

        // Start BFS from (0, 0) with cost 0
        buckets[0].push_back({0, 0});
        int pending = 1, currCost = 0;

        // 4 directions: right, down, left, up
        vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

        while (pending > 0)
        {
            int idx = currCost % (MAX_COST + 1);

            // If current bucket is empty, move to next cost level
            if (buckets[idx].empty()) 
            {
                currCost++;
                continue;
            }

            auto [r, c] = buckets[idx].front();
            buckets[idx].pop_front();
            pending--;

            // Skip if already found a better path to this cell
            if (dist[r][c] < currCost) continue;

            // Explore neighbors
            for (auto& d : dirs) 
            {
                int nr = r + d[0], nc = c + d[1];

                // Skip out-of-bound neighbors
                if (nr < 0 || nc < 0 || nr >= m || nc >= n) continue;

                int nextCost = grid[nr][nc];
                int totalCost = currCost + nextCost;

                // Relaxation: update if found a cheaper path
                if (dist[nr][nc] > totalCost) 
                {
                    dist[nr][nc] = totalCost;
                    buckets[totalCost % (MAX_COST + 1)].push_back({nr, nc});
                    pending++;
                }
            }
        }

        return dist[m-1][n-1];
    }
};

/*
🧠 Detailed Approach (0–k BFS):

- Edge weights are integers from 0 to 3 → so we use bucketed BFS (aka 0–k BFS).
- Instead of a normal queue, we maintain multiple "buckets" (deques) — one for each possible cost mod (k+1).
- Each cell push is done to the correct bucket based on its total cost.
- We process buckets in increasing cost order without using a heap.
- This gives us Dijkstra-level accuracy without the overhead of a priority queue.

📈 Time Complexity: O(m * n * k), where k = 3 → practically linear for small k.
📦 Space Complexity: O(m * n + k)

✅ This technique is super useful when edge weights are small bounded integers like 0, 1, 2, 3.
*/
