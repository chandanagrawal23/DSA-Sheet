class Solution 
{
public:
    const int MOD = 1e9 + 7;
    vector<vector<pair<int, int>>> graph;         // Adjacency list: node → {neighbor, weight}
    vector<int> shortestDistanceFromN;            // Dijkstra: shortest distance from node i to node n
    vector<int> dp;                               // Memoization for DFS results

    int countRestrictedPaths(int n, vector<vector<int>>& edges) 
    {
        // Step 1: Build graph
        graph.resize(n + 1);
        for (auto& edge : edges) 
        {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // Step 2: Run Dijkstra from node n to compute shortestDistanceFromN
        shortestDistanceFromN.assign(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, n});               // {distance, node}
        shortestDistanceFromN[n] = 0;

        while (!pq.empty()) 
        {
            auto [dist, node] = pq.top();
            pq.pop();

            if (dist > shortestDistanceFromN[node]) 
                continue;

            for (auto& [nei, weight] : graph[node]) 
            {
                if (dist + weight < shortestDistanceFromN[nei]) 
                {
                    shortestDistanceFromN[nei] = dist + weight;
                    pq.push({shortestDistanceFromN[nei], nei});
                }
            }
        }

        // Step 3: DFS from node 1 to n, using memoization
        dp.assign(n + 1, -1);
        return dfs(1, n);
    }

    int dfs(int node, int n) 
    {
        if (node == n) return 1;   // Reached destination

        if (dp[node] != -1) return dp[node];

        int ways = 0;
        for (auto& [child, _] : graph[node]) 
        {
            // Only follow paths where distance strictly decreases
            if (shortestDistanceFromN[node] > shortestDistanceFromN[child]) 
            {
                ways = (ways + dfs(child, n)) % MOD;
            }
        }
        return dp[node] = ways;
    }
};

/*
    -----------------------
    ✅ DETAILED APPROACH:
    -----------------------

    Problem:
    Count the number of "restricted paths" from node 1 to node n.

    A restricted path is a valid path where the shortest distance to node `n` strictly decreases at each step.

    -------------------------
    🔹 Step-by-step Approach:
    -------------------------

    1. Build an undirected weighted graph using adjacency list.
    
    2. Use **Dijkstra’s algorithm** starting from node `n` to calculate the shortest distances
       from every node to node `n`. Let's call this array `shortestDistanceFromN[]`.

       Example: If shortestDistanceFromN[2] = 4, that means shortest distance from node 2 to node n is 4.

    3. Now, we want to count all paths from node `1` to node `n`, such that:
       - For every consecutive pair (u, v) in the path:
           `shortestDistanceFromN[u] > shortestDistanceFromN[v]`

       This ensures we are always moving toward node `n` via nodes that are "closer" to it.

    4. We use **DFS + memoization**:
       - Start from node 1.
       - For each neighbor, if `shortestDistanceFromN[current] > shortestDistanceFromN[neighbor]`,
         then we can go to that neighbor and recurse from there.
       - Memoize the result to avoid recomputation.

    5. Return number of such restricted paths from node 1 to node n, modulo 1e9 + 7.

    -----------------------
    ⏱ Time Complexity:
    -----------------------
    - Dijkstra: O(E log V)
    - DFS traversal with memoization: O(V + E)
    - Total: Efficient for constraints (up to 2 * 10^4 edges)

    -----------------------
    🧠 Intuition:
    -----------------------
    - Dijkstra helps rank nodes by closeness to node `n`
    - DFS ensures we only follow paths with strictly decreasing distance to `n`

*/
