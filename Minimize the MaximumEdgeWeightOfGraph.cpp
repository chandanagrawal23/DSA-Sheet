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

Given graph is from u to v

now question says we should reach node 0 from every node, so instead of that
by reversing the edges we can say, we should reach to any node from node 0

Now we apply binary search over answer , let say my MID is answer, so for MID i want to check whether I 
can reach to all nodes from 0 or not.

*/
