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

class Solution
{
public:
    bool isCyclic(int n, const vector<vector<int>>& edges)
    {
        DSU dsu(n);

        for (const auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            // If u and v already belong to the same component, a cycle is found
            if (dsu.sameComponent(u, v))
                return true;

            // Otherwise, merge their components
            dsu.unite(u, v);
        }

        return false; // No cycles found
    }
};

int main()
{
    Solution sol;

    // Undirected graph with a cycle: 0-1-2-0
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << boolalpha << sol.isCyclic(3, edges1) << "\n"; // true

    // Acyclic graph (tree): 0-1, 1-2
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}};
    cout << boolalpha << sol.isCyclic(3, edges2) << "\n"; // false

    return 0;
}
/*

 Approach:
------------
- Use DSU (Disjoint Set Union) to track connected components in an undirected graph.
- For each edge (u, v):
   → If u and v are in the same component → adding the edge forms a cycle → return true.
   → Else, union the sets of u and v.
- If all edges processed without finding a cycle, return false.

 Time Complexity:  O(E * α(N)) ≈ O(E), where E = number of edges and α is inverse Ackermann.
 Space Complexity: O(N), for DSU data structures (parent and size arrays).

*/





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// we can solve this using BFS and DFS too

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // BFS approach to detect a cycle in an undirected graph
    bool isCyclicBFS(int n, vector<vector<int>>& adj)
    {
        vector<int> visited(n, 0);

        for (int start = 0; start < n; ++start)
        {
            if (!visited[start])
            {
                queue<pair<int, int>> q;
                q.push({start, -1}); // {node, parent}
                visited[start] = 1;

                while (!q.empty())
                {
                    int node = q.front().first;
                    int parent = q.front().second;
                    q.pop();

                    for (int neighbor : adj[node])
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = 1;
                            q.push({neighbor, node});  // mark current node as parent
                        }
                        else if (neighbor != parent)
                        {
                            // neighbor is visited AND it's not our parent → cycle
                            return true;
                        }
                    }
                }
            }
        }

        return false;  // No cycles found in any component
    }
/******************************************************************************************************************************************8*/
    // DFS helper function
    bool dfs(int node, int parent, vector<vector<int>>& adj, vector<int>& visited)
    {
        visited[node] = 1;

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, node, adj, visited))
                    return true;
            }
            else if (neighbor != parent)
            {
                // Found a back edge to an already visited node that isn't our parent → cycle
                return true;
            }
        }

        return false;
    }

    // DFS wrapper
    bool isCyclicDFS(int n, vector<vector<int>>& adj)
    {
        vector<int> visited(n, 0);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (dfs(i, -1, adj, visited))
                    return true;
            }
        }

        return false;
    }
};

/*

Approach Explanation:
----------------------

🌐 Problem: Detect if an undirected graph contains a cycle.

✅ BFS Logic:
- Use a queue and push (node, parent).
- For every neighbor:
    - If not visited: mark and continue.
    - If visited and not parent → CYCLE.

✅ DFS Logic:
- Recursively explore unvisited neighbors.
- If you reach a visited node that is not the parent → CYCLE.

Why we check `neighbor != parent`?
- In an undirected graph, if a visited neighbor isn’t the parent,
  we must have reached it via a different path ⇒ cycle exists.

🕒 Time Complexity: O(V + E)
📦 Space Complexity: O(V) for visited array and recursion/queue

Use BFS if you prefer level-by-level iteration.  
Use DFS if recursion suits your style.

*/

