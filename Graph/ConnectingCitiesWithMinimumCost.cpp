#include <bits/stdc++.h>
using namespace std;

// Comparator function to sort edges based on cost
bool compare(const vector<int> &a, const vector<int> &b)
{
    return a[2] < b[2];
}

// Disjoint Set Union (Union Find) with Path Compression
class DSU
{
public:
    vector<int> parent;

    DSU(int n)
    {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // Each city is its own parent
    }

    int find(int u)
    {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    bool unite(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);

        if (pu != pv)
        {
            parent[pu] = pv;
            return true; // Union successful
        }
        return false; // Already connected
    }
};

class Solution
{
public:
    int minimumCost(int n, vector<vector<int>> &connections)
    {
        // Sort all connections by cost using custom comparator
        sort(connections.begin(), connections.end(), compare);

        DSU dsu(n);
        int totalCost = 0;
        int edgesUsed = 0;

        for (auto &conn : connections)
        {
            int u = conn[0];
            int v = conn[1];
            int cost = conn[2];

            if (dsu.unite(u, v))
            {
                totalCost += cost;
                edgesUsed++;

                if (edgesUsed == n - 1)
                {
                    return totalCost; // All cities connected
                }
            }
        }

        return -1; // Not enough edges to connect all cities
    }
};
/*
===================================================
 Approach: Kruskal's Algorithm + DSU (Union Find)
=====================================================
1. Sort all connections by cost (smallest to largest).
2. Use DSU to add connections that don’t create cycles.
3. For each valid connection:
   - Add its cost
   - Count how many edges are used
4. If we used (N - 1) edges → we have a spanning tree (all cities connected).
5. If fewer than (N - 1) connections were added, the graph is disconnected → return -1.

=============================
Time Complexity:
=============================
- O(E * log E): Sorting all connections (E = #edges)
- O(E * α(N)): Union-Find operations (almost constant time with path compression)
- Total: **O(E * log E)**

=============================
Space Complexity:
=============================
- O(N): DSU parent array
- O(1): Other variables

=============================

*/
