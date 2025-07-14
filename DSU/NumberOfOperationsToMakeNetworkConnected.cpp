class DSU
{
public:
    vector<int> parent;
    vector<int> componentSize;
    int totalComponents;

    // Constructor: Initialize DSU for n elements
    DSU(int n)
    {
        parent.resize(n);
        componentSize.assign(n, 1); // Every element is its own set of size 1
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        totalComponents = n;
    }

    // Find representative of the component with path compression
    int find(int node)
    {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }

    // Union the components of u and v using union by size
    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false;

        // Attach smaller component under the larger one
        if (componentSize[rootU] >= componentSize[rootV])
        {
            parent[rootV] = rootU;
            componentSize[rootU] += componentSize[rootV];
        }
        else
        {
            parent[rootU] = rootV;
            componentSize[rootV] += componentSize[rootU];
        }

        totalComponents--;
        return true;
    }

    // Check if u and v are in the same component
    bool sameComponent(int u, int v)
    {
        return find(u) == find(v);
    }

    // Return the size of the component containing u
    int getSize(int u)
    {
        return componentSize[find(u)];
    }

    // Return the current number of disjoint sets
    int getComponentCount()
    {
        return totalComponents;
    }
};
/*----------------------------------------------------------------------------------------------*/

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections)
    {
        if (connections.size() < n - 1)
            return -1; // Not enough cables to connect all components

        DSU dsu(n);

        for (auto& conn : connections)
        {
            int u = conn[0], v = conn[1];
            // connect the edge 
            dsu.unite(u, v);
        }

        // To connect C components, we need at least (C - 1) edges
        return dsu.getComponentCount() - 1;
    }
};

/*
 Explanation:
You need at least (n - 1) edges to connect n nodes.

Use DSU to merge components.

If an edge connects two already-connected components ⇒ it's redundant and can be reused.

Count total components, and return components - 1 operations needed.

 Time & Space Complexity:
Time: O(N + M * α(N))
(M = number of edges, α(N) is inverse Ackermann, nearly constant)

Space: O(N) for DSU arrays

// we can solve same for BFS or DFS too, just make adjacency list, count total componenets and asnwer will be totalComponenets - 1
*/
