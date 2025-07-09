class Solution 
{
public:
    int minimumObstacles(vector<vector<int>>& grid) 
    {
        int m = grid.size();
        int n = grid[0].size();

        // Direction vectors: down, up, right, left
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        // Min-heap: {cost, x, y}
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
        vector<vector<int>> minCost(m, vector<int>(n, INT_MAX));

        pq.push({0, 0, 0});
        minCost[0][0] = 0;

        while (!pq.empty()) 
        {
            auto [cost, x, y] = pq.top();
            pq.pop();

            if (x == m - 1 && y == n - 1) 
            {
                return cost;
            }

            if (cost > minCost[x][y]) continue;

            for (int dir = 0; dir < 4; dir++) 
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n) 
                {
                    int nextCost = cost + grid[nx][ny];

                    if (nextCost < minCost[nx][ny]) 
                    {
                        minCost[nx][ny] = nextCost;
                        pq.push({nextCost, nx, ny});
                    }
                }
            }
        }

        return -1; // Unreachable (shouldn't happen per constraints)
    }
};

/*
Approach:

We use Dijkstra's algorithm to find the minimum number of obstacles to remove:
- Each cell has a cost of 0 or 1 depending on grid[i][j].
- Use a min-heap to always expand the least-cost node first.
- For each neighbor, calculate the new cost and update if it is lower.
- Continue until reaching (m-1, n-1).

Time Complexity:  O((m * n) * log(m * n))
  - Each cell may enter the priority queue multiple times.

Space Complexity: O(m * n)
  - For cost tracking and priority queue.
*/
