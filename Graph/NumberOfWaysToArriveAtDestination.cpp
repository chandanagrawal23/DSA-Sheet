class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) 
    {
        const long long MOD = 1e9 + 7;
        vector<vector<pair<int, long long>>> adj(n);  // adjacency list

        // Build graph
        for (const auto& road : roads) 
        {
            int u = road[0], v = road[1];
            long long time = road[2];
            adj[u].push_back({v, time});
            adj[v].push_back({u, time});
        }

        vector<long long> dist(n, LLONG_MAX);  // shortest time to each node
        vector<long long> ways(n, 0);          // number of shortest paths to each node

        // Min-heap: {time, node}
        priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<>> pq;

        dist[0] = 0;       // starting point has 0 distance
        ways[0] = 1;       // one way to be at source (node 0)
        pq.push({0, 0});   // push source node

        while (!pq.empty()) 
        {
            auto [currTime, u] = pq.top();  // current distance and node
            pq.pop();

            if (currTime > dist[u])
                continue;  // already found a better path

            for (const auto& [v, time] : adj[u]) 
            {
                long long newTime = currTime + time;

                // Found shorter path to v
                if (newTime < dist[v]) 
                {
                    dist[v] = newTime;
                    ways[v] = ways[u];         // inherit path count
                    pq.push({newTime, v});
                } 
                // Found another shortest path to v
                else if (newTime == dist[v]) 
                {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }

        return ways[n - 1] % MOD;  // number of ways to reach destination
    }
};
/*

Approach Summary
Idea:
Use Dijkstra’s algorithm to compute the shortest distance from node 0 to every other node. 
While doing so, maintain a ways[] array to count the number of shortest paths to each node.

Time Complexity:
O(E × log V)

E is the number of roads (edges),

V is the number of intersections (nodes).

Each edge is relaxed once, and heap operations take log V.

Space Complexity:
O(V + E)

For adjacency list, distance and path arrays, and priority queue.

*/
