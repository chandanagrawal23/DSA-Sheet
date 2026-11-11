#include<bits/stdc++.h>
using namespace std;

class DSU 
{
public:
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b) return false;

        if(sz[a] < sz[b]) swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

class Solution {
public:
    vector<int> numIslandsAfterQueries( vector<vector<int>>& grid, vector<vector<int>>& positions ) 
    {
        int m = grid.size();
        int n = grid[0].size();

        DSU dsu(m * n);

        int islands = 0;

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        // Step 1: Count initial land cells
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1)
                    islands++;
            }
        }

        // Step 2: Build initial DSU
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {

                if(grid[i][j] == 0) continue;

                int id = i * n + j;

                // Only right and down to avoid duplicate unions
                if(j + 1 < n && grid[i][j + 1] == 1) {
                    if(dsu.unite(id, id + 1))
                        islands--;
                }

                if(i + 1 < m && grid[i + 1][j] == 1) {
                    if(dsu.unite(id, id + n))
                        islands--;
                }
            }
        }

        // Step 3: Process queries
        vector<int> ans;

        for(auto &p : positions) {
            int r = p[0];
            int c = p[1];

            // Already land: no change
            if(grid[r][c] == 1) {
                ans.push_back(islands);
                continue;
            }

            // Convert water to land
            grid[r][c] = 1;
            islands++;

            int id = r * n + c;

            for(int d = 0; d < 4; d++) {
                int nr = r + dx[d];
                int nc = c + dy[d];

                if(nr < 0 || nc < 0 || nr >= m || nc >= n)
                    continue;

                if(grid[nr][nc] == 0)
                    continue;

                int nid = nr * n + nc;

                if(dsu.unite(id, nid))
                    islands--;
            }

            ans.push_back(islands);
        }

        return ans;
    }
};

// This is more generalized , suppose if we have already some 1's in Matrix then how to do? 

// 1. Count Island and then proicess query
