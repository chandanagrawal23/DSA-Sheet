class Solution 
{
public:

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) 
    {
        using ll = long long;
        const ll INF = 1e12;

        // Step 1: Build the graph
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) 
        {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // Dijkstra from start (node 0)
        vector<ll> distFromStart(n, INF);
        distFromStart[0] = 0;
        priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> pq;
        pq.push({0, 0});

        while (!pq.empty()) 
        {
            auto [d, u] = pq.top(); pq.pop();
            if (d > distFromStart[u]) continue;
            for (auto& [v, w] : graph[u]) 
            {
                if (distFromStart[u] + w < distFromStart[v]) 
                {
                    distFromStart[v] = distFromStart[u] + w;
                    pq.push({distFromStart[v], v});
                }
            }
        }

        // Dijkstra from end (node n - 1)
        vector<ll> distToEnd(n, INF);
        distToEnd[n - 1] = 0;
        pq.push({0, n - 1});

        while (!pq.empty()) 
        {
            auto [d, u] = pq.top(); pq.pop();
            if (d > distToEnd[u]) continue;
            for (auto& [v, w] : graph[u]) 
            {
                if (distToEnd[u] + w < distToEnd[v]) 
                {
                    distToEnd[v] = distToEnd[u] + w;
                    pq.push({distToEnd[v], v});
                }
            }
        }

        // Step 3: Check if each edge is on any shortest path
        ll shortestPath = distFromStart[n - 1];
        vector<bool> result(edges.size(), false);

        for (int i = 0; i < edges.size(); ++i) 
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            // Check if this edge lies on some shortest path:
            // Option 1: Edge u → v is in forward direction
            // Option 2: Edge v → u is in reverse direction
            if ((distFromStart[u] + w + distToEnd[v] == shortestPath) || 
                (distFromStart[v] + w + distToEnd[u] == shortestPath)) 
            {
                result[i] = true;
            }
        }

        return result;
    }
};


/*

APPROACH:
---------
We are given an undirected weighted graph and need to find which edges lie on **at least one shortest path** 
from node 0 to node n-1.

To do that, we run **Dijkstra twice**:
    1. From node 0 → gives distFromStart[], the shortest distance from node 0 to all other nodes.
    2. From node n-1 → gives distToEnd[], the shortest distance from each node to node n-1.

WHY TWO DIJKSTRAS?
------------------
→ We want to check for an edge (u, v, w) if it's part of any shortest path.
To be part of a shortest path from 0 to n-1, this must be true:

    // Option 1: Edge u → v is in forward direction
    distFromStart[u] + w + distToEnd[v] == shortestPathLength

    // Option 2: Edge v → u is in reverse direction
    distFromStart[v] + w + distToEnd[u] == shortestPathLength

Without running Dijkstra from node n-1, we cannot compute distToEnd[] and thus can't validate the above condition.

REAL-LIFE ANALOGY:
------------------
Imagine you're planning a trip from **Home (0)** to **Office (n-1)**. You want to check if a particular road segment (u ↔ v)
is part of the fastest way to reach your office.

- Dijkstra from home tells you how long it takes to reach any location from home.
- Dijkstra from office tells you how long it takes to reach office from any location.

Now, to check if a road segment (u, v, w) lies on a shortest path:
- Try joining the shortest route from Home to `u`, then this road `w`, and then from `v` to Office.
- If the total cost is equal to the shortest possible time, this road is valid.

TIME COMPLEXITY:
----------------
- Dijkstra: O((N + M) log N)
- Two Dijkstra runs: O(2 * (N + M) log N)
- Checking edges: O(M)
- Total: O((N + M) log N)

SPACE COMPLEXITY:
-----------------
- O(N + M) for graph and distances

*/
