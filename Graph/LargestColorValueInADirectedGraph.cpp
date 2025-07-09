// using DP + TOPO-Sorting
class Solution
{
public:
    int largestPathValue(string colors, vector<vector<int>>& edges)
    {
        int n = colors.size();
        vector<vector<int>> graph(n);         // Adjacency list representation of the graph
        vector<int> indegree(n, 0);           // Number of incoming edges to each node

        // Step 1: Build the graph and calculate indegrees
        for (const auto& edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            graph[from].push_back(to);
            indegree[to]++;
        }

        // Step 2: Initialize color frequency DP table
        // dp[i][c] represents the maximum count of color 'a'+c that can be collected on a path ending at node i
        vector<vector<int>> dp(n, vector<int>(26, 0));
        queue<int> q;

        // Step 3: Push all nodes with 0 indegree into the queue
        // These are starting points of valid paths (no prerequisites)
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
                dp[i][colors[i] - 'a'] = 1;  // The node contributes 1 to its own color count
            }
        }

        int maxCount = 0;     // Will store the final result
        int visited = 0;      // Count of how many nodes are processed (used for cycle detection)

        // Step 4: Standard Topological Sort using Kahn's Algorithm
        while (!q.empty())
        {
            int node = q.front(); q.pop();
            visited++;

            // For the current node, find max color count and update global max
            maxCount = max(maxCount, *max_element(dp[node].begin(), dp[node].end()));

            // Step 5: Process neighbors of the current node
           for (int neighbor : graph[node])
            {
                for (int color = 0; color < 26; color++)
                {
                    // Check if this color matches the neighbor's actual color
                    bool isSameColor = (colors[neighbor] - 'a' == color);

                    // New count = path from node + 1 if neighbor adds same color
                    int newCount = dp[node][color] + (isSameColor ? 1 : 0);

                    // Take the best (max) color count path to neighbor
                    dp[neighbor][color] = max(dp[neighbor][color], newCount);
                }
                // Decrease indegree and if it becomes 0, push to queue
                if (--indegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        // Step 6: If not all nodes were visited, graph contains a cycle → return -1
        return (visited == n) ? maxCount : -1;
    }
};
/*
🧠 DETAILED APPROACH:

You're given a **directed graph** with `n` nodes, where each node has a **color** (`'a'` to `'z'`). 
You're asked to find the **maximum number of times a single color appears** on **any valid path** in the graph. 
But if the graph has a **cycle**, return -1.

📌 Goal:
Return the largest number of same-color nodes on any path.

🎯 Core Idea:
Use **Topological Sort** + **Dynamic Programming per node per color**.

----------------------------------------------------
🔗 Step-by-Step Explanation:

1️⃣ Build the graph:
   - Create an adjacency list `graph[u] = {v1, v2, ...}` for all directed edges.
   - Track indegree for each node to help with topological sort.

2️⃣ Create a DP table:
   - `dp[i][c]` → max number of color `'a'+c` seen on any path ending at node `i`.
   - Initialize `dp[i][colors[i]-'a'] = 1` for all source nodes (nodes with indegree 0).

3️⃣ Topological Sort:
   - Use Kahn’s Algorithm (BFS using indegree).
   - At each node `u`, for each neighbor `v`, propagate color frequency:
     - For each color `c`, update:
       `dp[v][c] = max(dp[v][c], dp[u][c] + (colors[v] == c ? 1 : 0))`
     - That means: "Take the best count from the current node for each color,
       and if the neighbor node adds the same color, increment the count."

4️⃣ Update answer during traversal:
   - For each node, keep track of the maximum color count seen.

5️⃣ Detect Cycle:
   - If the number of visited nodes != total nodes → there's a cycle → return -1.

----------------------------------------------------
🧮 Time Complexity:
- O(N + E + 26 * N)
  - N = number of nodes
  - E = number of edges
  - 26 = for each alphabet color, per node update

🗂️ Space Complexity:
- O(N * 26 + E)

----------------------------------------------------

WHAT A QUESTION MAN

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// using DFS

class Solution 
{
public:
    // DFS function returns max color count at this node OR INT_MAX if cycle found
    int dfs(int node, string &colors, vector<vector<int>> &adj, vector<vector<int>> &count, vector<int> &vis) 
    {
        if (vis[node] == 1) 
        {
            return INT_MAX; // cycle detected
        }

        if (vis[node] == 2) 
        {
            return count[node][colors[node] - 'a']; // already processed
        }

        vis[node] = 1; // mark as visiting

        for (int next : adj[node]) 
        {
            // recursively process children
            if (dfs(next, colors, adj, count, vis) == INT_MAX)
            {
                return INT_MAX; // cycle detected in child
            }

            // update color frequency from child to current
            for (int c = 0; c < 26; c++) 
            {
                count[node][c] = max(count[node][c], count[next][c]);
            }
        }

        // increment count for current node's own color
        count[node][colors[node] - 'a']++;

        vis[node] = 2; // mark as fully processed

        return count[node][colors[node] - 'a'];
    }

    int largestPathValue(string colors, vector<vector<int>> &edges) 
    {
        int n = colors.size();

        vector<vector<int>> adj(n);         // adjacency list
        vector<vector<int>> count(n, vector<int>(26, 0)); // color count per node
        vector<int> vis(n, 0);              // 0 = unvisited, 1 = visiting, 2 = visited

        for (auto &e : edges) 
        {
            adj[e[0]].push_back(e[1]); // build graph
        }

        int maxColor = 0;

        for (int i = 0; i < n; i++) 
        {
            int result = dfs(i, colors, adj, count, vis);
            if (result == INT_MAX)
            {
                return -1; // cycle detected
            }
            maxColor = max(maxColor, result);
        }

        return maxColor;
    }
};
/*

📌 Goal:
Find the max number of any color in a path. If there's a cycle → return -1.

🛠️ Strategy:
- Use DFS to traverse each node.
- Track how many times each color has appeared in the path to this node using `count[i][c]`.
- Detect cycles using a `vis` vector:
    0 → not visited
    1 → visiting (active call stack)
    2 → fully visited
- If you revisit a `vis == 1` node → cycle → return INT_MAX
- While returning from DFS, update parent color counts from children.

⏱️ Time: O(N + E) * 26 → For each node and each color
📦 Space: O(N * 26 + N + E)


*/
