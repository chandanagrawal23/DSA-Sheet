#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union (Union Find)
class UnionFind
{
private:
    vector<int> parent;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // Initially, each node is its own parent
    }

    // Find with path compression
    int findParent(int node)
    {
        if (node != parent[node])
        {
            parent[node] = findParent(parent[node]);
        }
        return parent[node];
    }

    // Union two sets
    void unionSets(int u, int v)
    {
        int pu = findParent(u);
        int pv = findParent(v);
        parent[pu] = pv;
    }
};

// Comparator to sort edges by weight
bool compareByWeight(const vector<int> &a, const vector<int> &b)
{
    return a[2] < b[2];
}

class Solution
{
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
    {
        vector<int> critical;
        vector<int> pseudoCritical;

        // Add original index to each edge
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].push_back(i); // edges[i] = [u, v, weight, original_index]
        }

        // Sort edges by weight using custom comparator
        sort(edges.begin(), edges.end(), compareByWeight);

        // Find base MST weight without forcing or blocking any edge
        int baseMST = findMST(n, edges, -1, -1);

        for (int i = 0; i < edges.size(); i++)
        {
            // Check if edge is critical: if MST without it has larger weight
            if (findMST(n, edges, i, -1) > baseMST)
            {
                critical.push_back(edges[i][3]);
            }
            // Check if edge is pseudo-critical: if forcing it yields same MST weight
            else if (findMST(n, edges, -1, i) == baseMST)
            {
                pseudoCritical.push_back(edges[i][3]);
            }
        }

        return {critical, pseudoCritical};
    }

private:
    // Kruskal’s algorithm with options to:
    // - blockIndex: ignore this edge
    // - forceIndex: include this edge at start
    int findMST(int n, vector<vector<int>> &edges, int blockIndex, int forceIndex)
    {
        UnionFind uf(n);
        int totalWeight = 0;

        // Force include one edge if specified
        if (forceIndex != -1)
        {
            vector<int> &edge = edges[forceIndex];
            totalWeight += edge[2];
            uf.unionSets(edge[0], edge[1]);
        }

        // Run Kruskal’s algorithm
        for (int i = 0; i < edges.size(); i++)
        {
            if (i == blockIndex)
                continue;

            int u = edges[i][0], v = edges[i][1], w = edges[i][2];

            if (uf.findParent(u) != uf.findParent(v))
            {
                uf.unionSets(u, v);
                totalWeight += w;
            }
        }

        // Verify all nodes are connected
        for (int i = 0; i < n; i++)
        {
            if (uf.findParent(i) != uf.findParent(0))
            {
                return INT_MAX; // Not fully connected
            }
        }

        return totalWeight;
    }
};

/*
Approach:
---------
We need to find all Critical and Pseudo-Critical edges in the Minimum Spanning Tree (MST)
of a given undirected weighted graph.

Definitions:
------------
- Critical Edge: If removing this edge increases the MST cost or disconnects the graph,
  then it's critical.
- Pseudo-Critical Edge: If forcibly including this edge still gives the same MST cost,
  it's considered pseudo-critical.

Steps:
------
1. First, we append the original index to each edge so we can track it later.
   => edges[i] = [u, v, weight, original_index]

2. Sort all edges based on their weight (for Kruskal's algorithm).

3. Compute the MST cost without excluding or forcing any edge.
   This is the base MST cost.

4. For each edge:
   - Try **excluding** it and recompute the MST.
     - If excluding increases the MST cost (or disconnects the graph), mark it as critical.
   - Else, try **including** it forcibly first and then run Kruskal on the remaining edges.
     - If MST cost remains the same, it is pseudo-critical.

5. Return the result in two vectors: [critical_edges, pseudo_critical_edges]

Functions Used:
---------------
- UnionFind (Disjoint Set Union): Efficient structure to manage connected components.
- findMST: A modified Kruskal’s algorithm that optionally blocks or forces an edge
  in the MST construction.

Time Complexity:
----------------
- Sorting edges: O(E log E)
- For each edge, we compute MST possibly twice ⇒ O(E^2 * α(N)) where α is inverse Ackermann.
  Total: O(E^2 * α(N))

Space Complexity:
-----------------
- O(N + E) for graph representation, DSU, and tracking MST info.

This is an optimal and accepted approach to solve the Leetcode Hard problem:
"Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree".
*/

