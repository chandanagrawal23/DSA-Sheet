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
            parent[max(rootV,rootU)] = min(rootV,rootU);
            componentSize[rootU] += componentSize[rootV];
        }
        else
        {
            parent[max(rootV,rootU)] = min(rootV,rootU);
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
/*--------------------------------------------------------------------------------------------*/

class Solution
{
public:
    string smallestEquivalentString(string s1, string s2, string baseStr)
    {
        DSU dsu(26); // 26 lowercase letters

        // Union equivalent characters
        for (int i = 0; i < s1.size(); ++i)
        {
            dsu.unite(s1[i] - 'a', s2[i] - 'a');
        }

        // Replace each char in baseStr with the smallest equivalent
        for (char &ch : baseStr)
        {
            ch = dsu.find(ch - 'a') + 'a';
        }

        return baseStr;
    }
};

/*
Approach:
---------
This problem is about finding the lexicographically smallest string after replacing each character
in baseStr with its smallest equivalent character based on given equivalence rules from s1 and s2.

We use a DSU where:
- Each node represents a letter (0 to 25)
- We union the characters in s1 and s2, treating them as equal
- While uniting, we always point the larger character to the smaller one (to ensure smallest lex char becomes root)
- After DSU is built, for each character in baseStr, we replace it with the root of its equivalence class

Key Idea:
→ Always point lexicographically larger to the smaller in `unite()`
→ This ensures `find()` gives the smallest equivalent character

Time Complexity: O(N + M), where N = length of s1/s2, M = length of baseStr
Space Complexity: O(26)
*/
