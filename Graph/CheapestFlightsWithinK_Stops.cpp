class Solution 
{
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) 
    {
        // Adjacency list: city → {neighbor, price}
        vector<pair<int, int>> adjList[n];
        for (auto& flight : flights) 
        {
            int from = flight[0], to = flight[1], price = flight[2];
            adjList[from].push_back({to, price});
        }

        // Min cost to reach each city
        vector<int> minCost(n, 1e7);
        minCost[src] = 0;

        // Queue holds: {city, current total cost}
        queue<pair<int, int>> q;
        q.push({src, 0});

        // Perform BFS for up to k + 1 levels (k stops means k + 1 edges)
        while (k-- >= 0 && !q.empty()) 
        {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) 
            {
                auto [city, costSoFar] = q.front();
                q.pop();

                for (auto& [nextCity, flightCost] : adjList[city]) 
                {
                    int newCost = costSoFar + flightCost;

                    // Only proceed if this path gives a better cost
                    if (newCost < minCost[nextCity]) 
                    {
                        minCost[nextCity] = newCost;
                        q.push({nextCity, newCost});
                    }
                }
            }
        }

        return minCost[dst] == 1e7 ? -1 : minCost[dst];
    }
};

/*
Approach:

- We use a **BFS-based level traversal**, where each level represents one additional stop.
- `k` stops = at most `k+1` edges, so we do BFS for `k+1` levels.
- At each level, we only update costs if the new route gives a cheaper value.
- If we reach `dst` within `k` stops, return the minimum cost.

Why not Dijkstra?
- Dijkstra doesn't naturally handle stop limits unless we track stops too.
- BFS layer-wise traversal works well here due to the stop constraint.

Time Complexity:  O(k * E)
  - At each level (up to k+1), we process all edges from the queue.
Space Complexity: O(n + E)
  - For adjacency list and cost arrays.
*/
