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

/*------------------------------------------------------------------------------------------------------------------------------------------*/

class Solution {
public:
    bool equationsPossible(vector<string>& equations) 
    {
        DSU dsu(26);  // 26 lowercase English letters

        // Step 1: Process all equalities first and unite them
        for (const string& eq : equations) 
        {
            if (eq[1] == '=') 
            {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                dsu.unite(u, v);
            }
        }

        // Step 2: Process inequalities and check for conflicts
        for (const string& eq : equations) 
        {
            if (eq[1] == '!') 
            {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                if (dsu.sameComponent(u, v)) 
                {
                    return false;
                }
            }
        }

        return true;
    }
};

/*
Approach:
---------
This problem is about checking the satisfiability of a set of equality and inequality equations 
between lowercase English variables ('a' to 'z').

1. Use Disjoint Set Union (DSU) to group variables that are equal.
2. For each equation of the form "a==b", we merge a and b into the same component.
3. For each equation of the form "a!=b", we check:
   - If a and b already belong to the same component, then it's a contradiction → return false.

If no contradictions are found, all equations are satisfiable.

Time Complexity: O(α(N)) per operation, total O(26 + E), where E = number of equations
Space Complexity: O(26)
*/
