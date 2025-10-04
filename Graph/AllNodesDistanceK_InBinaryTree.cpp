/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// BFS with parent mapping

class Solution
{
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k)
    {
        unordered_map<TreeNode*, TreeNode*> parent; // map each node to its parent
        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;

        // Step 1: BFS to record parent relationships
        q.push(root);
        while (!q.empty())
        {
            TreeNode* curr = q.front();
            q.pop();

            if (curr->left)
            {
                parent[curr->left] = curr;
                q.push(curr->left);
            }
            if (curr->right)
            {
                parent[curr->right] = curr;
                q.push(curr->right);
            }
        }

        // Step 2: BFS from target node to find nodes at distance K
        q.push(target);
        visited[target] = true;
        int currLevel = 0;

        while (!q.empty())
        {
            int size = q.size();
            if (currLevel == k) 
                break;
            currLevel++;
            
            for (int i = 0; i < size; i++)
            {
                TreeNode* curr = q.front();
                q.pop();

                // immediate left
                if (curr->left && !visited[curr->left])
                {
                    visited[curr->left] = true;
                    q.push(curr->left);
                }
                
                // immediate right
                if (curr->right && !visited[curr->right])
                {
                    visited[curr->right] = true;
                    q.push(curr->right);
                }

                //it's parent
                if (parent[curr] && !visited[parent[curr]])
                {
                    visited[parent[curr]] = true;
                    q.push(parent[curr]);
                }
            }
        }

        vector<int> result;
        while (!q.empty())
        {
            result.push_back(q.front()->val);
            q.pop();
        }

        return result;
    }
};

/*
APPROACH:
---------
1. Perform a BFS from the root to map each node to its parent.
   - This allows us to move both downward (to children) and upward (to parent).

2. Start another BFS from the target node:
   - Each BFS level corresponds to 1 unit of distance.
   - After traversing K levels, all nodes currently in the queue
     are exactly K distance away from the target.

3. Use a visited map to avoid revisiting nodes.

Why BFS Works:
--------------
- BFS explores all nodes level by level, so it perfectly models
  distance-based traversal in a tree.
- The parent map converts the tree into an undirected graph,
  allowing movement in all directions.

Time Complexity:  O(N)
Space Complexity: O(N)
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////

// DFS with parent mapping


class Solution
{
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k)
    {
        unordered_map<TreeNode*, TreeNode*> parent;
        addParent(root, nullptr, parent);

        vector<int> result;
        unordered_set<TreeNode*> visited;
        dfs(target, k, result, visited, parent);
        return result;
    }

private:
    void addParent(TreeNode* node, TreeNode* par, unordered_map<TreeNode*, TreeNode*>& parent)
    {
        if (!node)
            return;

        parent[node] = par;
        addParent(node->left, node, parent);
        addParent(node->right, node, parent);
    }

    void dfs(TreeNode* node, int dist, vector<int>& result, unordered_set<TreeNode*>& visited, unordered_map<TreeNode*, TreeNode*>& parent)
    {
        if (!node || visited.count(node))
            return;

        visited.insert(node);

        if (dist == 0)
        {
            result.push_back(node->val);
            return;
        }

        dfs(parent[node], dist - 1, result, visited, parent);
        dfs(node->left, dist - 1, result, visited, parent);
        dfs(node->right, dist - 1, result, visited, parent);
    }
};

/*
Approach:
1. First, assign parent pointers for each node using DFS.
2. Then start DFS from target node, moving left, right, and parent until distance k.
3. Use a visited set to avoid revisiting nodes.

Time: O(N)
Space: O(N)
*/

/////////////////////////////////////////////////////////////////////////////////////////

// DFS on Builted Undirected Graph

class Solution
{
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k)
    {
        unordered_map<int, vector<int>> graph;
        buildGraph(root, nullptr, graph);

        vector<int> result;
        unordered_set<int> visited;
        visited.insert(target->val);

        dfs(target->val, 0, k, graph, visited, result);
        return result;
    }

private:
    void buildGraph(TreeNode* node, TreeNode* par, unordered_map<int, vector<int>>& graph)
    {
        if (!node)
            return;

        if (par)
        {
            graph[node->val].push_back(par->val);
            graph[par->val].push_back(node->val);
        }

        buildGraph(node->left, node, graph);
        buildGraph(node->right, node, graph);
    }

    void dfs(int node, int dist, int k, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited, vector<int>& result)
    {
        if (dist == k)
        {
            result.push_back(node);
            return;
        }

        for (int nei : graph[node])
        {
            if (!visited.count(nei))
            {
                visited.insert(nei);
                dfs(nei, dist + 1, k, graph, visited, result);
            }
        }
    }
};

/*
Approach:
1. Convert the binary tree into an undirected graph (bidirectional edges).
2. Perform DFS from target node until distance K.
3. Use visited set to avoid cycles.

Time: O(N)
Space: O(N)
*/
