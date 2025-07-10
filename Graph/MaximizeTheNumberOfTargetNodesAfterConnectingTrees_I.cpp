class Solution
{
public:

    // DFS helper to count how many nodes can be reached from `node` within a depth limit
    int dfs(int node, int parent, const vector<vector<int>> &graph, int depth)
    {
        if (depth < 0)
            return 0; // stop when depth runs out

        int total = 1; // count this node

        for (int neighbor : graph[node])
        {
            if (neighbor != parent) // prevent revisiting parent
            {
                total += dfs(neighbor, node, graph, depth - 1);
            }
        }

        return total;
    }

    // Build graph from edge list and compute number of nodes reachable from each node up to given depth
    vector<int> build(const vector<vector<int>> &edges, int depth)
    {
        int n = edges.size() + 1; // total number of nodes = edges + 1
        vector<vector<int>> graph(n);

        // Construct undirected adjacency list
        for (const auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> result(n);

        // For each node, perform DFS to count reachable nodes within given depth
        for (int i = 0; i < n; ++i)
        {
            result[i] = dfs(i, -1, graph, depth);
        }

        return result;
    }

    vector<int> maxTargetNodes(vector<vector<int>> &edges1, vector<vector<int>> &edges2, int k)
    {
        // Step 1: Count reachable nodes from each node in tree1 with depth `k`
        vector<int> count1 = build(edges1, k);

        // Step 2: Count reachable nodes from each node in tree2 with depth `k-1`
        // Why k-1? Because we assume there's a cross-edge from tree1 to tree2 which costs 1 unit,
        // leaving k-1 steps to explore further in tree2.
        vector<int> count2 = build(edges2, k - 1);

        // Step 3: Since we can jump to *any* node in tree2, choose the one that gives max reach
        int maxCount2 = *max_element(count2.begin(), count2.end());

        int n = count1.size();
        vector<int> result(n);

        // Step 4: For each node in tree1, assume we teleport to best node in tree2
        // Final answer = count in tree1 (within depth k) + best count in tree2 (within depth k - 1)
        for (int i = 0; i < n; ++i)
        {
            result[i] = count1[i] + maxCount2;
        }

        return result;
    }
};

/*

🔍 APPROACH EXPLAINED IN DETAIL:

We are given two trees:
- `edges1` represents the first tree with N nodes.
- `edges2` represents the second tree with N nodes.

The goal is:
➡️ For each node `i` in tree1:
    - Count how many nodes you can reach from `i` within a depth of `k` in tree1.
    - Then teleport to *any* node `j` in tree2.
    - From node `j`, count how many nodes you can reach within depth `k-1` in tree2.
    - (Why k-1? Because 1 move is used in teleporting between trees.) ?

        Depth k in Tree1
        Jump immediately to Tree2 (cost = 1 step)
        Then we only have k - 1 steps left for Tree2
- so that is why we calculate count1 array which tells us the number of nodes from "i" we can reach at max depth K for tree 1
- same , nodes from "i" we can reach at max depth K-1 for tree 2 

Now we want to connect node i (of tree1 ) and we want to connect to that node (j of tree2) which contain max nodes (means max value of count2 array)

So for each node `i` in tree1, the maximum number of nodes you can reach is:
    ➡️ count1[i] + max(count2[j]) for all j in tree2

We do the following:
1. Use DFS to build count1[] = reachable node count from each node in tree1 with depth `k`
2. Use DFS to build count2[] = reachable node count from each node in tree2 with depth `k - 1`
3. Find the maximum value in count2[] (since you can jump to any node in tree2)
4. For each i in tree1: result[i] = count1[i] + maxCount2

🕒 Time Complexity:
- O(N²) worst case because for each node we may do DFS up to depth `k`
- Acceptable if N ≈ 1000 and depth is small

🧠 Space Complexity:
- O(N) for graph, visited stack, and result arrays

This logic allows us to merge best results from both trees, while staying within a total distance constraint of `k`.

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////

// same approach using BFS - 

class Solution
{
public:

    // BFS helper to count how many nodes can be reached from `start` within `maxDepth`
    int bfs(int start, const vector<vector<int>> &graph, int maxDepth)
    {
        int n = graph.size();
        vector<bool> visited(n, false);
        queue<pair<int, int>> q; // pair = {node, current depth}

        q.push({start, 0});
        visited[start] = true;

        int count = 0;

        while (!q.empty())
        {
            auto [node, depth] = q.front();
            q.pop();

            if (depth > maxDepth)
                continue;

            count++;

            for (int neighbor : graph[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push({neighbor, depth + 1});
                }
            }
        }

        return count;
    }

    // Build graph from edge list and compute number of nodes reachable from each node up to given depth using BFS
    vector<int> build(const vector<vector<int>> &edges, int maxDepth)
    {
        int n = edges.size() + 1;
        vector<vector<int>> graph(n);

        // Construct adjacency list
        for (const auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> result(n);

        // Perform BFS from each node
        for (int i = 0; i < n; ++i)
        {
            result[i] = bfs(i, graph, maxDepth);
        }

        return result;
    }

    vector<int> maxTargetNodes(vector<vector<int>> &edges1, vector<vector<int>> &edges2, int k)
    {
        // Step 1: For each node in Tree1, count reachable nodes within depth `k`
        vector<int> count1 = build(edges1, k);

        // Step 2: For Tree2, compute reachable nodes from each node within depth `k - 1`
        vector<int> count2 = build(edges2, k - 1);

        // Step 3: Pick the best node from Tree2 (i.e., one with max reach)
        int maxCount2 = *max_element(count2.begin(), count2.end());

        // Step 4: Combine both for each node in Tree1
        int n = count1.size();
        vector<int> result(n);
        for (int i = 0; i < n; ++i)
        {
            result[i] = count1[i] + maxCount2;
        }

        return result;
    }
};
