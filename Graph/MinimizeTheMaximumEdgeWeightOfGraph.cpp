class Solution
{
public:
    // Helper function to check if all nodes can be visited from node 0
    // using only edges with weight <= mid
    bool isValid(int n, int mid, vector<vector<pair<int, int>>> &adj)
    {
        vector<int> visited(n, 0);  // Track visited nodes
        queue<int> q;
        q.push(0);                  // Start BFS from node 0
        visited[0] = 1;
        int count = 0;              // Count of reachable nodes

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            // Explore neighbors with weight <= mid
            for (auto it : adj[node])
            {
                if (!visited[it.first] && it.second <= mid)
                {
                    q.push(it.first);
                    visited[it.first] = 1;
                }
            }
        }

        // Return true if all nodes are reachable
        return count == n;
    }

    // Main function to return the minimum maximum weight
    // such that all nodes are reachable from node 0
    int minMaxWeight(int n, vector<vector<int>> &edges, int threshold)
    {
        // Build the adjacency list (directed graph)
        vector<vector<pair<int, int>>> adj(n);
        int maxWeight = 0;

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[v].push_back({u, wt});  // Reverse edge to go from u -> v
            maxWeight = max(maxWeight, wt);
        }

        // Binary Search on possible max weights
        int low = 0, high = maxWeight, ans = 1e9;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            // Check if using only edges with weight <= mid allows full reachability
            if (isValid(n, mid, adj))
            {
                ans = mid;        // Possible answer found
                high = mid - 1;   // Try to find a smaller one
            }
            else
            {
                low = mid + 1;    // Increase weight limit
            }
        }

        return (ans == 1e9) ? -1 : ans;  // Return -1 if no valid weight found
    }
};

/*

/*
Given graph edges are from u → v.

But the question asks if all nodes can reach node 0. To simplify,
we reverse the edges so it becomes: can node 0 reach all other nodes?

Now apply binary search on the edge weight.
For each mid value, check if we can reach all nodes from node 0
using only edges with weight ≤ mid.

Time Complexity:
- O(E * logW), where W is the range of weights (max - min),
  and E is the number of edges processed during BFS in each iteration.

Space Complexity:
- O(N + E) for adjacency list and visited array.
*/
