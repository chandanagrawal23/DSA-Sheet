#include <bits/stdc++.h>
using namespace std;

class DSU 
{
public:
    vector<int> parent;
    DSU(int n) 
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // each node is its own parent initially
    }

    int find(int x) 
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    void unite(int x, int y) 
    {
        int xr = find(x);
        int yr = find(y);
        if (xr != yr)
            parent[yr] = xr; // merge components
    }
};

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) 
    {
        DSU dsu(c+1); // 1-based indexing

        // Step 1: Build connected components
        for (auto &e : connections) 
        {
            dsu.unite(e[0], e[1]);
        }

        // Step 2: For each component, store online nodes in a sorted set
        unordered_map<int, set<int>> compNodes;
        for (int i=1; i<=c; i++) 
        {
            int root = dsu.find(i);
            compNodes[root].insert(i);
        }

        vector<bool> online(c+1, true); // all stations initially online
        vector<int> result;

        // Step 3: Process queries
        for (auto &q : queries) 
        {
            int type = q[0], x = q[1];
            int root = dsu.find(x);

            if (type == 1) // maintenance check
            {
                if (online[x]) 
                {
                    result.push_back(x); // station itself resolves
                } 
                else 
                {
                    if (compNodes[root].empty()) 
                        result.push_back(-1); // no online station in grid
                    else 
                        result.push_back(*compNodes[root].begin()); // smallest online station
                }
            } 
            else // type == 2 → station goes offline
            {
                if (online[x]) 
                {
                    online[x] = false;
                    compNodes[root].erase(x); // remove from its component set
                }
            }
        }

        return result;
    }
};

/**
Approach:
1. Use DSU to group stations into connected components (grids).
2. Maintain a set<int> for each component to keep track of currently online stations.
   - Set is ordered, so *begin() gives the smallest online station.
3. Process queries:
   - [1, x]: If x is online → return x. Else return smallest online station in its component (or -1 if none).
   - [2, x]: Mark station x offline and erase it from its component’s set.
4. Complexity:
   - DSU build: O(c + n α(c))
   - Each query: O(log c) due to set operations
   - Overall: O((c+n) + q log c)
**/
