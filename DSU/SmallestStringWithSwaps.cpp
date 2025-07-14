#include <bits/stdc++.h>
using namespace std;

/*-----------------------------------------------------         DSU CLASS        ----------------------------------------------------------*/
class DSU
{
public:
    vector<int> parent;
    vector<int> componentSize;
    int totalComponents;

    DSU(int n)
    {
        parent.resize(n);
        componentSize.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
        totalComponents = n;
    }

    int find(int node)
    {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }

    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false;

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

    int getComponentCount()
    {
        return totalComponents;
    }
};
/*--------------------------------------------------------------------------------------------------------------------------------------*/

class Solution
{
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs)
    {
        int n = s.size();
        DSU dsu(n);

        // Unite indices based on allowed swaps
        for (auto& pair : pairs)
        {
            dsu.unite(pair[0], pair[1]);
        }

        // Group all indices by their connected component
        unordered_map<int, vector<int>> groupMap;
        for (int i = 0; i < n; i++)
        {
            int root = dsu.find(i);
            groupMap[root].push_back(i);
        }

        // For each group, sort the characters and place them back
        for (auto& [root, indices] : groupMap)
        {
            string temp;
            for (int idx : indices)
                temp += s[idx];

            sort(temp.begin(), temp.end());

            for (int i = 0; i < indices.size(); ++i)
                s[indices[i]] = temp[i];
        }

        return s;
    }
};


/*

 Approach: DSU + Component Sorting

- Each pair [i, j] means characters at i and j can be swapped directly or indirectly.
- We model this as a graph and find all connected components using Disjoint Set Union (DSU).
- For each connected component:
   → Collect all indices.
   → Extract their characters.
   → Sort the characters.
   → Place them back in lexicographical order.

Why this works:
- Sorting characters within each swappable group ensures that we get the lexicographically smallest result.

 Time Complexity:
- O(N log N) for sorting all characters across components (in total).
- O(N + M * α(N)) for DSU operations (N = string length, M = number of pairs)

 Space Complexity:
- O(N) for DSU, groups, and character storage.

*/
