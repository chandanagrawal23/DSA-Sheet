// Approach 1: Postorder DFS (Tree DP) 
class Solution {
public:

    // Returns finish time of current subtree
    long long dfs(int node, vector<vector<int>> &adj, vector<int> &baseTime) {

        // Leaf node
        if (adj[node].empty())
            return baseTime[node];

        long long mn = LLONG_MAX;
        long long mx = LLONG_MIN;

        // Process all children first (Postorder DFS)
        for (int child : adj[node]) {
            long long childFinish = dfs(child, adj, baseTime);

            mn = min(mn, childFinish);
            mx = max(mx, childFinish);
        }

        long long ownDuration = (mx - mn) + baseTime[node];

        return mx + ownDuration;
    }

    long long finishTime(int n, vector<vector<int>> &edges, vector<int> &baseTime) {

        // Parent -> Children
        vector<vector<int>> adj(n);

        for (auto &e : edges)
            adj[e[0]].push_back(e[1]);

        return dfs(0, adj, baseTime);
    }
};

/* 

Approach 1: Postorder DFS (Tree DP)
====================================
Idea
Since the graph is a tree, every child is processed before its parent.
For every node:
If it's a leaf → finishTime = baseTime.
Otherwise, compute the minimum and maximum finish time among all children, then calculate the current node's finish time.
Time Complexity  : O(n)
Space Complexity : O(n) (Recursion stack + adjacency list)

*/


//-------------------------------------------------------------------------------------------------------------------------------


// Approach 2: Bottom-Up (Leaf → Root using Queue)


class Solution {
public:
    long long finishTime(int n, vector<vector<int>> &edges, vector<int> &baseTime) {

        // Reverse graph : Child -> Parent
        vector<vector<int>> parent(n);

        // Number of children of every node
        vector<int> outDeg(n, 0);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            parent[v].push_back(u);
            outDeg[u]++;
        }

        vector<long long> mn(n, LLONG_MAX);
        vector<long long> mx(n, LLONG_MIN);
        vector<long long> finish(n);

        queue<int> q;

        // Push all leaf nodes
        for (int i = 0; i < n; i++) {
            if (outDeg[i] == 0) {
                q.push(i);

                // Leaf finish = baseTime
                mn[i] = 0;
                mx[i] = 0;
            }
        }

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            // finish = latest + ((latest-earliest)+base)
            finish[node] = 2LL * mx[node] - mn[node] + baseTime[node];

            // Update every parent
            for (int par : parent[node]) {

                mn[par] = min(mn[par], finish[node]);
                mx[par] = max(mx[par], finish[node]);

                // One child completed
                outDeg[par]--;

                // All children processed
                if (outDeg[par] == 0)
                    q.push(par);
            }
        }

        return finish[0];
    }
};






/*
  
Approach 2: Bottom-Up (Leaf → Root using Queue)
==================================================
Idea
Start from all leaf nodes.
Compute their finish time immediately.
Propagate their finish time to their parent.
Once all children of a parent are processed, compute the parent's finish time.
Continue until reaching the root.

Time Complexity : O(n)
Space Complexity : O(n)
*/
