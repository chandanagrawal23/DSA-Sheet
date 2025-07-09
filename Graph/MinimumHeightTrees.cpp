class Solution 
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) 
    {
        if (n == 0)
        {
            return {};
        }

        if (n == 1)
        {
            return {0}; // Single node is itself a MHT
        }

        vector<vector<int>> adj(n);       // Adjacency list
        vector<int> degree(n, 0);         // Track degree of each node

        // Build the graph
        for (auto& edge : edges) 
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        queue<int> q;

        // Add all leaf nodes (degree == 1)
        for (int i = 0; i < n; i++) 
        {
            if (degree[i] == 1) 
            {
                q.push(i);
            }
        }

        vector<int> res;

        // Remove leaf layers one by one
        while (!q.empty()) 
        {
            int size = q.size();
            res.clear(); // store current layer

            for (int i = 0; i < size; i++) 
            {
                int node = q.front();
                q.pop();
                res.push_back(node); // this layer's leaf node

                for (int neighbor : adj[node]) 
                {
                    degree[neighbor]--; // Remove edge to current leaf
                    if (degree[neighbor] == 1) 
                    {
                        q.push(neighbor); // It becomes new leaf
                    }
                }
            }
        }

        return res; // Remaining 1 or 2 nodes are centroids
    }
};

/*
📌 Problem:
You’re given an undirected tree (connected & acyclic). Return all possible roots such that the resulting tree has minimum height.

💡 Intuition:
In a tree, the Minimum Height Tree roots are always at the center — i.e., one or two nodes from which all longest paths are minimized.

🎯 Strategy:
- This is like peeling an onion.
- Remove all leaf nodes layer by layer until 1 or 2 nodes remain.
- These remaining nodes are the centroids (roots of MHT).

🧩 Why 1 or 2 nodes remain?
Because a tree can have at most 2 centroids (in case of even-length diameter).

🛠️ Steps:
1. Build adjacency list and count degrees.
2. Push all leaf nodes (degree == 1) into a queue.
3. While queue is not empty:
   - Clear `res` (current layer of leaves)
   - Remove current leaves and update degrees.
   - Any node whose degree becomes 1 → new leaf
4. The last set of `res` nodes remaining are centroids.

⏱️ Time Complexity: O(N)
📦 Space Complexity: O(N)


*/
