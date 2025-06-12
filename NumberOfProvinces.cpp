// using BFS

class Solution
{
public:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinceCount = 0;

        for (int city = 0; city < n; ++city)
        {
            if (!visited[city])
            {
                bfs(isConnected, city, visited);
                provinceCount++;  // Found a new province
            }
        }

        return provinceCount;
    }

    void bfs(vector<vector<int>>& graph, int start, vector<bool>& visited)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
            {
                if (graph[current][neighbor] == 1 && !visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

/*
Approach (BFS):
- For each unvisited city, start BFS to mark all connected cities.
- Each BFS traversal covers one province.

Time: O(n^2) — Traverse adjacency matrix
Space: O(n) — Visited array + BFS queue
*/






// using DFS

#include <vector>
using namespace std;

class Solution
{
public:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinceCount = 0;

        for (int city = 0; city < n; ++city)
        {
            if (!visited[city])
            {
                dfs(isConnected, city, visited);
                provinceCount++;  // Found a new province
            }
        }

        return provinceCount;
    }

    void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited)
    {
        visited[node] = true;

        for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
        {
            if (graph[node][neighbor] == 1 && !visited[neighbor])
            {
                dfs(graph, neighbor, visited);
            }
        }
    }
};

/*
Approach (DFS):
- For each unvisited city, do DFS to mark all reachable cities.
- Each such DFS marks a full province.
- Count how many DFS runs were needed.

Time: O(n^2) — Traverse the adjacency matrix
Space: O(n) — Visited array + recursion stack
*/
