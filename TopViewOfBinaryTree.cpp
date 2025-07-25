#include <bits/stdc++.h>
using namespace std;

// -------------------------------
// Definition of TreeNode
// -------------------------------
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// -------------------------------
// Solution Class with Top View
// -------------------------------
class Solution
{
public:
    // -----------------------------------------------------
    // 1. TOP VIEW USING BFS
    // -----------------------------------------------------
    // Idea:
    // - Perform level order traversal (BFS).
    // - Keep track of horizontal distance (HD) of each node from root.
    // - Root has HD = 0, left child = HD - 1, right child = HD + 1.
    // - For each HD, store the **first node** encountered during BFS
    //   (this ensures topmost node for that vertical column is stored).
    // - Use a map<int, int> to store HD -> node value mapping.
    // - Finally, return node values in order from leftmost HD to rightmost HD.
    // -----------------------------------------------------
    vector<int> topView(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        queue<pair<TreeNode*, int>> q;      // {node, HD}
        map<int, int> hdMap;                // HD -> first seen node

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            if (hdMap.find(hd) == hdMap.end())  // topmost at this HD
                hdMap[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        for (auto& [hd, val] : hdMap)  // collect in left-to-right order
            result.push_back(val);

        return result;
    }

    // -----------------------------------------------------
    // 2. TOP VIEW USING DFS
    // -----------------------------------------------------
    // Idea:
    // - Traverse the tree recursively.
    // - Keep track of horizontal distance (HD) and level (depth).
    // - For each HD, store the first node that appears at the smallest depth.
    // - If another node comes at same HD but deeper level, ignore it.
    // -----------------------------------------------------
    void dfs(TreeNode* node, int hd, int level, map<int, pair<int, int>>& hdMap)
    {
        if (!node) return;

        // only take the node if no node at this HD or comes from a shallower level
        if (hdMap.find(hd) == hdMap.end() || level < hdMap[hd].second)
            hdMap[hd] = {node->val, level};

        dfs(node->left, hd - 1, level + 1, hdMap);
        dfs(node->right, hd + 1, level + 1, hdMap);
    }

    vector<int> topViewDFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        map<int, pair<int, int>> hdMap;  // HD -> {node_val, level}
        dfs(root, 0, 0, hdMap);

        for (auto& [hd, val_level] : hdMap)
            result.push_back(val_level.first);

        return result;
    }
};

// -------------------------------
// Main function to test the solution
// -------------------------------
int main()
{
    /*
         Constructing the following tree:
                1
               / \
              2   3
               \   \
                4   5
               /     \
              6       7

        Top View: 2 1 3 5 7
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    Solution sol;

    vector<int> topBFS = sol.topView(root);
    cout << "Top View (BFS): ";
    for (int x : topBFS) cout << x << " ";
    cout << endl;

    vector<int> topDFS = sol.topViewDFS(root);
    cout << "Top View (DFS): ";
    for (int x : topDFS) cout << x << " ";
    cout << endl;

    return 0;
}

/*
------------------------------------------------------------
Approach Summary:
------------------------------------------------------------

1. **Top View using BFS**:
   - Use level-order traversal.
   - Track each node's horizontal distance (HD) from the root.
   - For each HD, keep the **first** node encountered (topmost at that HD).
   - Result is collected from leftmost HD to rightmost HD using map.

2. **Top View using DFS**:
   - Traverse tree recursively (DFS).
   - For each node, track its HD and depth (level).
   - Store the node if it's the **first seen** at that HD or at a shallower depth.
   - Result is collected in order of increasing HD using map.

------------------------------------------------------------
Time Complexity: O(N * log N)
------------------------------------------------------------
- Both BFS and DFS visit each node once => O(N)
- Each insertion in `map` takes O(log N)

------------------------------------------------------------
Space Complexity: O(N)
------------------------------------------------------------
- BFS queue or DFS recursion stack => O(H) where H is height (≤ N)
- Map stores up to N nodes in worst case => O(N)

------------------------------------------------------------
*/
