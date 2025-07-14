
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

/*---------------------------------------------------------------------------------*/

class Solution
{
public:
    int regionsBySlashes(vector<string> &grid)
    {
        int n = grid.size();
        int total = 4 * n * n; // each cell is split into 4 parts (0:top, 1:right, 2:bottom, 3:left)
        DSU dsu(total);

        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                int base = 4 * (row * n + col);
                char ch = grid[row][col];

                // Internal connections inside a cell
                if (ch == ' ')
                {
                    dsu.unite(base + 0, base + 1);
                    dsu.unite(base + 1, base + 2);
                    dsu.unite(base + 2, base + 3);
                }
                else if (ch == '/')
                {
                    dsu.unite(base + 0, base + 3);
                    dsu.unite(base + 1, base + 2);
                }
                else if (ch == '\\')
                {
                    dsu.unite(base + 0, base + 1);
                    dsu.unite(base + 2, base + 3);
                }

                // Connect with right neighbor
                if (col + 1 < n)
                {
                    int rightBase = 4 * (row * n + (col + 1));
                    dsu.unite(base + 1, rightBase + 3);
                }
                // Connect with bottom neighbor
                if (row + 1 < n)
                {
                    int bottomBase = 4 * ((row + 1) * n + col);
                    dsu.unite(base + 2, bottomBase + 0);
                }
            }
        }

        return dsu.totalComponents;
    }
};

/**
Approach:
- Treat each cell as divided into 4 triangular parts.
- Use DSU to merge parts within a cell based on its content:
  - ' ' connects all 4 parts
  - '/' connects (top-left) and (right-bottom)
  - '\' connects (top-right) and (bottom-left)
- Also connect neighboring parts between adjacent cells:
  - Right edge with left of right cell
  - Bottom edge with top of bottom cell
- Finally, return total number of connected components in the DSU

Time Complexity: O(N^2)
Space Complexity: O(N^2)
*/


//////////////////////////////////////////////////////////////////////////
// Regions Cut By Slashes - Using DFS on Expanded Grid
/////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int regionsBySlashes(vector<string> &grid)
    {
        int n = grid.size();
        int size = 3 * n;
        vector<vector<bool>> visited(size, vector<bool>(size, false));

        // Mark the cells for '/' and '\'
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                char ch = grid[r][c];
                int baseRow = 3 * r;
                int baseCol = 3 * c;

                if (ch == '/')
                {
                    visited[baseRow][baseCol + 2] = true;
                    visited[baseRow + 1][baseCol + 1] = true;
                    visited[baseRow + 2][baseCol] = true;
                }
                else if (ch == '\')
                {
                    visited[baseRow][baseCol] = true;
                    visited[baseRow + 1][baseCol + 1] = true;
                    visited[baseRow + 2][baseCol + 2] = true;
                }
            }
        }

        int regions = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (!visited[i][j])
                {
                    dfs(i, j, size, visited);
                    regions++;
                }
            }
        }

        return regions;
    }

private:
    void dfs(int row, int col, int n, vector<vector<bool>> &visited)
    {
        if (row < 0 || row >= n || col < 0 || col >= n || visited[row][col])
            return;

        visited[row][col] = true;

        dfs(row + 1, col, n, visited);
        dfs(row - 1, col, n, visited);
        dfs(row, col + 1, n, visited);
        dfs(row, col - 1, n, visited);
    }
};

/**
Approach:
- Expand the original NxN grid into a 3N x 3N grid.
- Each '/' and '\' is drawn by marking its respective diagonal cells in the 3x3 block as visited.
- Then use DFS to count the number of connected components of unvisited cells.
- Each DFS call discovers a distinct region.

Time Complexity: O(N^2)
Space Complexity: O(N^2)
*/
