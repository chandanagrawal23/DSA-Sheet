#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> parent;

public:
    DSU(int n)
    {
        parent.resize(n, -1);
    }

    int find(int x)
    {
        if (parent[x] == -1) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y) parent[max(x, y)] = min(x, y);
    }
};

class Solution
{
public:
    string smallestEquivalentString(string s1, string s2, string baseStr)
    {
        DSU dsu(26);
        for (int i = 0; i < s1.size(); ++i)
            dsu.unite(s1[i] - 'a', s2[i] - 'a');

        for (char &ch : baseStr)
            ch = dsu.find(ch - 'a') + 'a';

        return baseStr;
    }
};

/*
Approach:
- Use DSU to group equivalent characters.
- Always keep the lexicographically smallest character as the parent.
- For each character in baseStr, find its representative and replace it.
*/
