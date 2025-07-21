class Solution 
{
public:
    bool canReachWithinLimit(const vector<vector<pair<int, int>>>& graph, 
                             const vector<bool>& online, 
                             long long allowedWeight, 
                             long long maxAllowedCost)
    {
        int n = graph.size();
        vector<long long> minCost(n, LLONG_MAX); // min cost to reach each node
        minCost[0] = 0;

        // Min-heap: {cost_so_far, node}
        priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<>> pq;
        pq.push({0, 0});

        while (!pq.empty()) 
        {
            long long currentCost = pq.top()[0];
            int node = pq.top()[1];
            pq.pop();

            if (currentCost > minCost[node]) continue;
            if (!online[node]) continue;

            for (const auto& edge : graph[node]) 
            {
                int neighbor = edge.first;
                int weight = edge.second;

                // Only allow edges meeting the minimum weight condition
                if (weight < allowedWeight) continue;
                if (!online[neighbor]) continue;

                long long newCost = currentCost + weight;

                // Prune if over budget
                if (newCost > maxAllowedCost) continue;

                if (newCost < minCost[neighbor]) 
                {
                    minCost[neighbor] = newCost;
                    pq.push({newCost, neighbor});
                }
            }
        }

        // Return whether we can reach the last node within allowed cost
        return minCost[n - 1] <= maxAllowedCost;
    }

    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) 
    {
        int n = online.size();
        long long low = 0, high = -1, result = -1;

        // Build graph only with online nodes
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) 
        {
            if (online[edge[0]] && online[edge[1]])
            {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];
                graph[u].push_back({v, weight});
                high = max(high, static_cast<long long>(weight));
            }
        }

        // Binary search for maximum allowedWeight such that a path exists
        while (low <= high) 
        {
            long long allowedWeight = (low + high) / 2;

            if (canReachWithinLimit(graph, online, allowedWeight, k)) 
            {
                result = allowedWeight;
                low = allowedWeight + 1;
            } 
            else 
            {
                high = allowedWeight - 1;
            }
        }

        return result;
    }
};

/*
APPROACH:
----------
- Build a graph using only the online nodes.
- Use binary search on the minimum allowed edge weight (allowedWeight), trying to find the **maximum value**
  such that we can still reach from node 0 to node n-1 within cost <= k.

- For each mid (allowedWeight), use Dijkstra's algorithm (min-heap) to find the shortest cost path using only
  edges with weight >= allowedWeight.

- If the shortest path cost is within budget (k), it’s a valid answer — we try a higher threshold.
  Else, we reduce the weight limit.

TIME COMPLEXITY:
----------------
- Let E = number of edges, N = number of nodes
- Binary search runs in O(logW), where W is the max edge weight
- For each iteration, Dijkstra runs in O(E log N)
- Total = O(E log N * logW)

SPACE COMPLEXITY:
-----------------
- O(N + E) for the graph + minCost + priority queue
*/
