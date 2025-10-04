#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    void dfs(int node, unordered_set<int>& visited, const vector<vector<int>>& adj)
    {
        visited.insert(node);
        for (int next : adj[node])
        {
            if (visited.find(next) == visited.end())
            {
                dfs(next, visited, adj);
            }
        }
    }

public:
    int maximumDetonation(vector<vector<int>>& bombs)
    {
        int n = bombs.size();
        vector<vector<int>> adj(n);

        // Build directed graph
        for (int i = 0; i < n; i++)
        {
            long long x1 = bombs[i][0];
            long long y1 = bombs[i][1];
            long long r1 = bombs[i][2];

            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;

                long long x2 = bombs[j][0];
                long long y2 = bombs[j][1];
                long long dx = x2 - x1;
                long long dy = y2 - y1;

                // j lies within or on i's explosion radius → i can trigger j
                if (dx * dx + dy * dy <= r1 * r1)
                {
                    adj[i].push_back(j);
                }
            }
        }

        int maxExplosions = 0;

        // Try detonating each bomb as the start
        for (int i = 0; i < n; i++)
        {
            unordered_set<int> visited;
            dfs(i, visited, adj);
            maxExplosions = max(maxExplosions, (int)visited.size());
        }

        return maxExplosions;
    }
};

/*
APPROACH (DFS):
---------------
1. Treat each bomb as a node in a directed graph.
   Add a directed edge i → j if the center of bomb j lies inside or on the explosion circle of bomb i.

   Geometrically:
     - Each bomb defines a circle with center (x1, y1) and radius r1.
     - The distance between two centers (x1, y1) and (x2, y2) is:
           d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
     - If d <= r1, then i’s explosion reaches j.

   To avoid floating-point sqrt, we compare squares:
       (x2 - x1)^2 + (y2 - y1)^2 <= r1^2

   This means the center of bomb j lies inside or exactly on bomb i’s circle boundary.

   Note: Circle overlap ≠ detonation.
         Overlap just means perimeters touch or intersect,
         but we specifically check if j’s center is inside i’s blast area.

2. Build the adjacency list (directed edges).

3. For each bomb:
      - Run DFS (or BFS) to count all bombs reachable from it.
      - Keep track of the maximum reachable count.

Why DSU fails:
--------------
- DSU can only find undirected connected components.
- Here, the reachability is directional:
     A → B doesn’t guarantee B → A.
- So we need DFS/BFS to simulate the directional chain reaction.

Time Complexity:  O(n²)
Space Complexity: O(n²)
*/

class Solution
{
private:
    int bfs(int start, const vector<vector<int>>& adj)  // <-- pass by const reference
    {
        queue<int> q;
        unordered_set<int> visited;

        q.push(start);
        visited.insert(start);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int next : adj[node])
            {
                if (visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return visited.size();
    }

public:
    int maximumDetonation(vector<vector<int>>& bombs)
    {
        int n = bombs.size();
        vector<vector<int>> adj(n);  // use vector<vector<int>> instead of vector<int> adj[n]

        // Build directed graph
        for (int i = 0; i < n; i++)
        {
            long long x1 = bombs[i][0];
            long long y1 = bombs[i][1];
            long long r1 = bombs[i][2];

            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;

                long long x2 = bombs[j][0];
                long long y2 = bombs[j][1];

                long long dx = x2 - x1;
                long long dy = y2 - y1;

                // If bomb j’s center lies inside or on i’s blast circle → i can trigger j
                if (dx * dx + dy * dy <= r1 * r1)
                {
                    adj[i].push_back(j);
                }
            }
        }

        int maxExplosions = 0;

        // Try detonating each bomb as the starting bomb
        for (int i = 0; i < n; i++)
        {
            maxExplosions = max(maxExplosions, bfs(i, adj));
        }

        return maxExplosions;
    }
};

/*
APPROACH (BFS):
---------------
1. Treat each bomb as a node in a directed graph.
   Add a directed edge i → j if the center of bomb j lies inside or on the explosion circle of bomb i.

   Geometrically:
     - Each bomb defines a circle with center (x1, y1) and radius r1.
     - The distance between two centers (x1, y1) and (x2, y2) is:
           d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
     - If d <= r1, then i’s explosion reaches j.

   To avoid floating-point sqrt, we compare squares:
       (x2 - x1)^2 + (y2 - y1)^2 <= r1^2

   This means the center of bomb j lies inside or exactly on bomb i’s circle boundary.

   Note: Circle overlap ≠ detonation.
         Overlap just means perimeters touch or intersect,
         but we specifically check if j’s center is inside i’s blast area.

2. Build the adjacency list (directed edges).

3. For each bomb:
      - Run DFS (or BFS) to count all bombs reachable from it.
      - Keep track of the maximum reachable count.

Why DSU fails:
--------------
- DSU can only find undirected connected components.
- Here, the reachability is directional:
     A → B doesn’t guarantee B → A.
- So we need DFS/BFS to simulate the directional chain reaction.

Time Complexity:  O(n²)
Space Complexity: O(n²)
*/
