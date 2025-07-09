#include <bits/stdc++.h>
using namespace std;

// DSU class for union-find
class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv)
            return false;

        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else if (rank[pu] > rank[pv])
            parent[pv] = pu;
        else
        {
            parent[pv] = pu;
            rank[pu]++;
        }
        return true;
    }
};

// Compare function (no lambda)
bool cmp(const vector<int> &a, const vector<int> &b)
{
    return a[2] < b[2];
}

class Solution
{
public:
    int minCostToSupplyWater(int n, vector<int> &wells, vector<vector<int>> &pipes)
    {
        vector<vector<int>> edges = pipes;

        // Add virtual edges from node 0 to each house
        for (int i = 0; i < n; i++)
        {
            edges.push_back({0, i + 1, wells[i]}); // virtual edge: node 0 to house i+1
        }

        sort(edges.begin(), edges.end(), cmp); // sort edges by cost

        DSU dsu(n);
        int totalCost = 0;

        for (auto &e : edges)
        {
            if (dsu.unite(e[0], e[1]))
            {
                totalCost += e[2];
            }
        }

        return totalCost;
    }
};
/*
Approach:
---------
- Each house has two choices:
  1. Build a well inside it (wells[i])
  2. Connect to another house with a pipe (pipes[][])

- We model "building a well" as a pipe from a **virtual node (0)** to the house with cost `wells[i]`.

- Now, we just find the **Minimum Spanning Tree (MST)** of the graph using Kruskal’s algorithm.

- The MST will automatically pick the cheapest option (well or pipe) to connect every house.

Steps:
------
1. Add all pipes to the edge list.
2. Add virtual edges from node 0 to each house with cost = wells[i].
3. Sort all edges by weight.
4. Use DSU (Disjoint Set Union) to build the MST and accumulate the total cost.

Time Complexity:
----------------
- O(E log E) where E = number of edges = pipes + n (wells)
- Union-Find operations are near-constant (amortized O(α(n)))

Space Complexity:
-----------------
- O(n) for DSU

*/
