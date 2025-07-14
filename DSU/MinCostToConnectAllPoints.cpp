/*-----------------------------------------------------         DSU CLASS        ----------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;

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

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<array<int, 3>> edges;

        // Generate all possible edges with their manhattan distances
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.push_back({dist, i, j});
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end());

        DSU dsu(n);
        int totalCost = 0;
        int edgesUsed = 0;

        // Pick the smallest edges while avoiding cycles
        for (auto &[cost, u, v] : edges)
        {
            if (dsu.unite(u, v))
            {
                totalCost += cost;
                edgesUsed++;
                if (edgesUsed == n - 1) 
                      break; // MST is complete
            }
        }

        return totalCost;
    }
};

/*
 APPROACH (Kruskal's Algorithm using DSU):
--------------------------------------------------
We're asked to connect all given points with minimum total cost using Manhattan distance.

 Strategy:
- Treat each point as a node in a graph.
- Form all possible edges between each pair of points with their manhattan distance as weight.
- Use Kruskal’s Minimum Spanning Tree (MST) algorithm to connect points:
   → Sort all edges by distance (cost)
   → Use DSU (Disjoint Set Union) to avoid cycles
   → Add the smallest edges until all points are connected

 Why DSU?
   - DSU helps keep track of connected components efficiently.
   - Union by size with path compression makes operations nearly O(1).

 Time Complexity:
   - O(N^2 log N): N^2 edges + sorting them
   - DSU ops are ~O(α(N)), nearly constant

 Space Complexity:
   - O(N^2) for storing all edges
   - O(N) for DSU arrays
*/
