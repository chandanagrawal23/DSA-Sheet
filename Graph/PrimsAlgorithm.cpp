#include<bits/stdc++.h>
using namespace std;

int findMSTCost(int n, vector<vector<pair<int, int>>>& graph) {
    vector<bool> visited(n, false);
    vector<int> minEdge(n, INT_MAX);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;

    minEdge[0] = 0;
    pq.push({0, 0}); // {cost, node}

    int totalCost = 0;

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();

        if (visited[u]) 
            continue;
        visited[u] = true;
        totalCost += cost;

        for (auto& [v, w] : graph[u]) 
        {
            if (!visited[v] && w < minEdge[v]) 
            {
                minEdge[v] = w;
                pq.push({w, v});
            }
        }
    }

    return totalCost;
}


vector<array<int, 3>> findMSTEdges(int n, vector<vector<pair<int, int>>>& graph) {
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> minEdge(n, INT_MAX);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;
    vector<array<int, 3>> mstEdges;

    minEdge[0] = 0;
    pq.push({0, 0}); // {cost, node}

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();

        if (visited[u]) 
            continue;
        visited[u] = true;

        if (parent[u] != -1) 
        {
            mstEdges.push_back({parent[u], u, cost});
        }

        for (auto& [v, w] : graph[u]) 
        {
            if (!visited[v] && w < minEdge[v]) 
            {
                minEdge[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    return mstEdges;
}
int main() 
{
    int n = 5;
    vector<vector<pair<int, int>>> graph(n);
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 2, 1},
        {1, 2, 3},
        {1, 3, 2},
        {2, 3, 8},
        {3, 4, 4}
    };

    for (auto& e : edges) 
    {
        int u = e[0], v = e[1], w = e[2];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int cost = findMSTCost(n, graph);
    cout << "MST Cost: " << cost << endl;

    auto mst = findMSTEdges(n, graph);
    cout << "MST Edges:\n";
    for (auto& [u, v, w] : mst) {
        cout << u << " -- " << v << " (weight " << w << ")\n";
    }

    return 0;
}

/*
=========================
💡 Prim’s Algorithm - Approach
=========================

We implement two versions:
--------------------------------
1️⃣ `findMSTCost(n, graph)`:
   - Computes the **minimum total weight** of the Minimum Spanning Tree (MST).

2️⃣ `findMSTEdges(n, graph)`:
   - Returns the actual **edges** used in the MST as a list of `{u, v, weight}`.

--------------------------------
🔧 How Prim's Algorithm Works:
--------------------------------
- Start with an arbitrary node (we choose node 0).
- Use a **min-heap (priority queue)** to always pick the edge with the least weight that connects an unvisited node.
- Maintain:
  - `minEdge[i]`: Minimum edge weight to reach node `i`.
  - `visited[i]`: Whether a node is already in the MST.
  - `parent[i]`: Parent node from which `i` was added to the MST (used only in `findMSTEdges`).

- In each step:
  - Extract the node with the smallest connecting edge.
  - Mark it as visited and update its neighbors if a better (smaller weight) edge is found.

--------------------------------
📦 Input Format:
- `n`: Number of nodes.
- `graph`: Adjacency list of format `graph[u] = vector of {v, weight}`.

- Note: The graph must be undirected and connected.

--------------------------------
⏱ Time Complexity:
- O(E * log V), where:
  - E = Number of edges
  - V = Number of vertices (nodes)
- Because for each edge, we may insert/update it in the priority queue (log V operations).

--------------------------------
💾 Space Complexity:
- O(V + E)
  - `graph` uses O(E)
  - `minEdge`, `visited`, `parent` arrays use O(V)
  - Priority queue stores at most O(E) entries in worst case.

--------------------------------
🧪 Example:
Edges: {0-1:10}, {0-2:1}, {1-2:3}, {1-3:2}, {2-3:8}, {3-4:4}

MST Cost: 10
MST Edges:
0 -- 2 (weight 1)
2 -- 1 (weight 3)
1 -- 3 (weight 2)
3 -- 4 (weight 4)

*/
