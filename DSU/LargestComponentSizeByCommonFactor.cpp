#include <bits/stdc++.h>
using namespace std;

/*------------------------------- DSU CLASS---------------------------------------*/
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

/*--------------------------------------------------------------------------------------*/

class Solution
{
public:
    int largestComponentSize(vector<int> &nums)
    {
        int maxVal = *max_element(nums.begin(), nums.end());
        DSU dsu(maxVal + 1); // Create DSU to cover all values up to max in nums

        // For each number, connect it with all its factors
        for (int num : nums)
        {
            for (int factor = 2; factor * factor <= num; factor++)
            {
                if (num % factor == 0)
                {
                    dsu.unite(num, factor);        // connect num with factor
                    dsu.unite(num, num / factor);  // connect num with its pair factor
                }
            }
        }

        unordered_map<int, int> groupFreq; // root -> frequency of component
        int maxGroupSize = 0;

        // Count the size of each component
        for (int num : nums)
        {
            int root = dsu.find(num);
            groupFreq[root]++;
            maxGroupSize = max(maxGroupSize, groupFreq[root]);
        }

        return maxGroupSize;
    }
};

/*
Approach:
We connect numbers that share any common factor using DSU.
1. For each number in the input, union it with all its factors (except 1).
2. After building all connections, we count the size of each connected component.
3. The component with the maximum size is our answer.

Time Complexity: O(N * sqrt(M))
- N = number of elements
- M = maximum element in nums (due to factorization up to sqrt(M))

Space Complexity: O(M)
- For DSU and frequency map, where M is the max value in nums
*/
