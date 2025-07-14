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
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/


class Solution {
public:
    vector<int>parent;
    int numSimilarGroups(vector<string>& strs) 
    {
        int n =  strs.size();
        DSU dsu(n);
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(canBeSimilar(strs[i],strs[j]))
                {
                    dsu.unite(i,j);
                }
            }
        }
        return dsu.getComponentCount();
    }
    
    bool canBeSimilar(string &a , string &b)
    {
        int cnt = 0;
        for(int i=0;i<a.size();i++)
        {
            if(a[i]!=b[i])
            {
                cnt++;
                if(cnt>2)
                    return false;
            }
        }
        return true;
    }
};

/*
 Approach:
------------
- We treat each string as a node in a graph.
- An edge is formed between two nodes if the corresponding strings are "similar".
- A group is a connected component of similar strings.

To find number of such groups:
→ Use DSU to unite all strings that are similar (either same or differ in exactly 2 places via a swap).
→ Count the number of disjoint components.

 How canBeSimilar() works:
→ If a and b are similar, they must differ at exactly 2 positions and swapping them should make the strings equal.

 Time Complexity:
- O(n² * m): for each pair of strings, we compare them character by character (m is string length)

 Space Complexity:
- O(n): for DSU parent/size arrays
*/
