#include <bits/stdc++.h>
using namespace std;

struct DSU 
{
    vector<int> parent, rank;

    DSU(int n) 
    {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) 
    {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) 
    {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false; // Already in same component

        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

int findMSTCost_Kruskal(int n, vector<array<int, 3>>& edges) 
{
    sort(edges.begin(), edges.end()); // Sort by weight
    DSU dsu(n);

    int totalCost = 0;
    for (auto& [w, u, v] : edges) 
    {
        if (dsu.unite(u, v)) 
        {
            totalCost += w;
        }
    }

    return totalCost;
}

vector<array<int, 3>> findMSTEdges_Kruskal(int n, vector<array<int, 3>>& edges) 
{
    sort(edges.begin(), edges.end()); // Sort by weight
    DSU dsu(n);

    vector<array<int, 3>> mst;
    for (auto& [w, u, v] : edges) 
    {
        if (dsu.unite(u, v)) 
        {
            mst.push_back({u, v, w});
        }
    }

    return mst;
}

int main() 
{
    int n = 5;
    vector<array<int, 3>> edges = {
        {10, 0, 1},
        {1, 0, 2},
        {3, 1, 2},
        {2, 1, 3},
        {8, 2, 3},
        {4, 3, 4}
    };

    int cost = findMSTCost_Kruskal(n, edges);
    cout << "MST Cost (Kruskal): " << cost << endl;

    auto mstEdges = findMSTEdges_Kruskal(n, edges);
    cout << "MST Edges (Kruskal):\n";
    for (auto& [u, v, w] : mstEdges) {
        cout << u << " -- " << v << " (weight " << w << ")\n";
    }

    return 0;
}
/*
=========================
💡 Kruskal’s Algorithm - Approach
=========================

We implement two versions:
--------------------------------
1️⃣ `findMSTCost_Kruskal(n, edges)`:
   - Returns the **total weight** of the Minimum Spanning Tree (MST).

2️⃣ `findMSTEdges_Kruskal(n, edges)`:
   - Returns the **actual MST edges** used.

--------------------------------
🧱 Steps of Kruskal’s Algorithm:
--------------------------------
1. Sort all edges by **weight (ascending)**.
2. Initialize **DSU (Disjoint Set Union)** to track connected components.
3. Iterate through edges:
   - If the nodes are in different components (i.e., not forming a cycle), include the edge in MST.
   - Otherwise, skip it.

4. Stop when MST has exactly `n - 1` edges (for `n` nodes).

--------------------------------
📦 Input Format:
- `n`: Number of nodes.
- `edges`: A list of `{weight, u, v}` edges (undirected).

--------------------------------
⏱ Time Complexity:
- Sorting edges: O(E * log E)
- DSU operations (with path compression + union by rank): ~O(α(N)) per op (α = inverse Ackermann, very small)
- Overall: O(E * log E)

💾 Space Complexity:
- O(N) for DSU (parent + rank)
- O(E) for storing edges and MST result

--------------------------------
🧪 Example:
Input Edges:
{0-1:10}, {0-2:1}, {1-2:3}, {1-3:2}, {2-3:8}, {3-4:4}

Sorted Edges:
{0-2:1}, {1-3:2}, {1-2:3}, {3-4:4}, {2-3:8}, {0-1:10}

MST Cost: 10
MST Edges:
0 -- 2 (1)
1 -- 3 (2)
1 -- 2 (3)
3 -- 4 (4)
*/
