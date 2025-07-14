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
    int earliestAcq(vector<vector<int>> &logs, int n)
    {
        sort(logs.begin(), logs.end()); // sort by timestamp

        DSU dsu(n);
        int components = n;

        for (const auto &log : logs)
        {
            int timestamp = log[0];
            int x = log[1];
            int y = log[2];

            if (dsu.unite(x, y))
            {
                components--;
            }

            if (components == 1)
            {
                return timestamp;
            }
        }

        return -1;
    }
};

/*
 Explanation:

DSU (Disjoint Set Union):
find(x): Gets the representative (parent) of x.
unite(x, y): Merges two sets if they are different. Returns true if a merge happened.

Approach:
-> Sort the logs by time.
-> Process each friendship using unite(x, y).
-> Keep track of how many components (friend groups) are left.
      When components == 1, everyone is connected → return that timestamp.

      If loop ends and not connected → return -1.

Time & Space Complexity:
----------------------------

Time: 

Sorting logs: O(m log m) where m = logs.size()
Union-Find operations: O(α(n)) per operation (almost constant)

Space: O(n) for DSU data structures


*/
