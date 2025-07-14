/*-----------------------------------------------------         DSU CLASS        ----------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> parent;
    vector<int> componentSize;
    int totalComponents,maxSize;

    // Constructor: Initialize DSU for n elements
    DSU(int n)
    {
        parent.resize(n);
        componentSize.assign(n, 1); // Every element is its own set of size 1
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        totalComponents = n;
        maxSize = 1;
    }

    // Find representative of the component with path compression
    int find(int node)
    {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }

    int largestGroup()
    {
        return maxSize;
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
            maxSize = max(maxSize, componentSize[rootU]);
        }
        else
        {
            parent[rootU] = rootV;
            componentSize[rootV] += componentSize[rootU];
            maxSize = max(maxSize, componentSize[rootV]);
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
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
class Solution
{
public:
    vector<int> groupStrings(vector<string>& words)
    {
        int n = words.size();
        DSU dsu(n);
        unordered_map<int, int> present;

        for (int i = 0; i < n; i++)
        {
            int bitMask = 0;

            // Convert word to bitmask
            for (char c : words[i])
            {
                bitMask |= (1 << (c - 'a'));
            }

            // Try all additions: adding a character (set bit j)
            for (int j = 0; j < 26; j++)
            {
                int newMask = bitMask | (1 << j);

                if (present.count(newMask))
                {
                    dsu.unite(present[newMask], i);
                }

                // Update last index of this new mask
                present[newMask] = i;
            }
        }

        return {dsu.getComponentCount(), dsu.largestGroup()};
    }
};

/*
 Intuition:
-------------
Each word can be represented as a 26-bit bitmask. Two words are similar if:
- We can convert one into the other by adding one character.

Instead of checking all 3 operations (add, delete, replace), we **only try add**.
Why?
Because:
- Any delete/replace can be covered when the shorter/altered word later tries to "add" the missing character.

So:
- For each word, try setting each of the 26 bits (one at a time).
- If that new bitmask exists in `present`, union it with current index.
- Update the current bitmask in the map with index.

 This ensures all possible reachable bitmasks are connected through DSU.

 Output:
- Number of disjoint groups (connected components)
- Size of the largest group

 Time Complexity:
- O(n * 26) = 26n ≈ O(n) where n = number of words

 Space Complexity:
- O(n + 2^26) in worst case due to bitmask map
*/
