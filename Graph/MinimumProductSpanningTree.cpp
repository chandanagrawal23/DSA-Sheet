#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Disjoint Set Union (Union-Find) with path compression
class DSU
{
    vector<int> parent;

public:
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv)
            return false;
        parent[pu] = pv;
        return true;
    }
};

// Comparator function to avoid using lambda
bool compareByLogWeight(const vector<int> &a, const vector<int> &b)
{
    return log(a[2]) < log(b[2]);
}

// Function to compute Minimum Product Spanning Tree
int minimumProductSpanningTree(int n, vector<vector<int>> &edges)
{
    // Sort edges by weight using comparator (to avoid overflow from product)
    sort(edges.begin(), edges.end(), compareByLogWeight);

    DSU dsu(n);
    long long product = 1;
    int count = 0;

    for (auto &e : edges)
    {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        if (dsu.unite(u, v))
        {
            product = (product * w) % MOD;
            count++;
        }
    }

    return count == n - 1 ? product : -1;
}

// Example usage
int main()
{
    int n = 4;
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 5}};

    int result = minimumProductSpanningTree(n, edges);
    if (result != -1)
        cout << "Minimum Product of Spanning Tree: " << result << endl;
    else
        cout << "Graph is not connected, no MST possible." << endl;

    return 0;
}
/*
Approach:
---------
- The goal is to find a Minimum Spanning Tree (MST) such that the product of the weights of the selected edges is minimized.
- We use Kruskal's algorithm to build the MST, which works by:
    1. Sorting all edges by weight.
    2. Iterating through the sorted list and using Union-Find (DSU) to pick edges that don't form a cycle.
    3. Instead of summing the weights (as in normal MST), we multiply the weights to get the total product.

- Since multiplying large numbers can cause overflow, we sort the edges by comparing log(weights) instead of actual values.
  This ensures correctness as log(a * b) = log(a) + log(b), and comparing logs is safe for sorting.

- After picking `n - 1` edges (for `n` nodes), we return the product modulo 1e9 + 7.
- If fewer than `n - 1` edges are used, the graph isn't connected → return -1.

Time Complexity:
----------------
- Sorting edges: O(E log E)
- Union-Find operations: O(E * α(N)), where α is the inverse Ackermann function (very small)
- Total: O(E log E)

Space Complexity:
-----------------
- O(N) for DSU parent array
- O(E) for edge list
*/
