#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union class
class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
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

// Sort edges by weight (no lambda)
bool compareByWeight(const vector<int> &a, const vector<int> &b)
{
    return a[2] < b[2];
}

// Function to check if (A, B) is present in edge list
bool edgeExists(const vector<vector<int>> &edges, int A, int B, int &edgeWeight)
{
    for (const auto &e : edges)
    {
        if ((e[0] == A && e[1] == B) || (e[0] == B && e[1] == A))
        {
            edgeWeight = e[2];
            return true;
        }
    }
    return false;
}

// Normal MST cost
int normalMSTCost(int n, const vector<vector<int>> &edges)
{
    DSU dsu(n);
    int total = 0;
    for (const auto &e : edges)
    {
        if (dsu.unite(e[0], e[1]))
            total += e[2];
    }
    return total;
}

// MST with edge (A, B) forced first
int forcedMSTCost(int n, const vector<vector<int>> &edges, int A, int B, int ABweight)
{
    DSU dsu(n);
    int total = 0;
    dsu.unite(A, B);
    total += ABweight;

    for (const auto &e : edges)
    {
        if (dsu.unite(e[0], e[1]))
            total += e[2];
    }
    return total;
}

// Main checker
bool isEdgeInAnyMST(int n, vector<vector<int>> edges, int A, int B)
{
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareByWeight);

    // First check if (A, B) is in edge list
    int ABweight = -1;
    if (!edgeExists(edges, A, B, ABweight))
        return false;

    int baseMST = normalMSTCost(n, edges);
    int withAB = forcedMSTCost(n, edges, A, B, ABweight);

    return baseMST == withAB;
}

// Sample Test
int main()
{
    vector<vector<int>> edges = {
        {0, 1, 20},
        {0, 2, 5},
        {0, 3, 10},
        {2, 3, 10}
    };

    int A = 2, B = 3;

    bool result = isEdgeInAnyMST(4, edges, A, B);
    cout << (result ? "True\n" : "False\n");

    return 0;
}
/*
Approach:
---------
We want to check whether the edge (A, B) is part of any Minimum Spanning Tree (MST).

Steps:
1. Check if (A, B) exists in the given edge list. If not, return false immediately.
2. Sort all edges by weight (ascending).
3. Compute MST cost normally using Kruskal's algorithm.
4. Compute MST cost by forcibly including edge (A, B) first, then proceeding with Kruskal.
5. If both MST costs match, then (A, B) is part of some MST.

Time Complexity:
----------------
- O(E log E) for sorting
- O(E * α(N)) for union-find operations (almost constant time)

Space Complexity:
-----------------
- O(N) for DSU

Why This Works:
---------------
If including (A, B) still produces the same minimum cost MST, then (A, B) is part of at least one valid MST.
*/
