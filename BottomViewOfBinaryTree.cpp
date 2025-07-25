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
// Solution Class with Bottom View
// -------------------------------
class Solution
{
public:
    // -----------------------------------------------------
    // 1. BOTTOM VIEW USING BFS
    // -----------------------------------------------------
    // Idea:
    // - Perform level order traversal (BFS)
    // - Track horizontal distance (HD) for each node
    // - Always update the node at a particular HD (last seen = bottom)
    // - Use map<int, int> to store HD -> value mapping
    // - At the end, map will contain the bottom-most node for each HD
    // -----------------------------------------------------
    vector<int> bottomViewBFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        queue<pair<TreeNode*, int>> q;      // {node, HD}
        map<int, int> hdMap;                // HD -> value

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // always update, last one seen at HD is bottom-most
            hdMap[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        for (auto& [hd, val] : hdMap)
            result.push_back(val);

        return result;
    }

    // -----------------------------------------------------
    // 2. BOTTOM VIEW USING DFS
    // -----------------------------------------------------
    // Idea:
    // - Traverse the tree using DFS
    // - At each node, record its value for current HD
    // - The last node visited at a given HD will overwrite the previous one
    // - Thus, the final map will contain the bottom-most node at each HD
    // -----------------------------------------------------
    void dfs(TreeNode* node, int hd, map<int, int>& hdMap)
    {
        if (!node) return;

        // always update for bottom-most
        hdMap[hd] = node->val;

        dfs(node->left, hd - 1, hdMap);
        dfs(node->right, hd + 1, hdMap);
    }

    vector<int> bottomViewDFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        map<int, int> hdMap;
        dfs(root, 0, hdMap);

        for (auto& [hd, val] : hdMap)
            result.push_back(val);

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

        Bottom View: 6 4 1 5 7
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    Solution sol;

    vector<int> bottomBFS = sol.bottomViewBFS(root);
    cout << "Bottom View (BFS): ";
    for (int x : bottomBFS) cout << x << " ";
    cout << endl;

    vector<int> bottomDFS = sol.bottomViewDFS(root);
    cout << "Bottom View (DFS): ";
    for (int x : bottomDFS) cout << x << " ";
    cout << endl;

    return 0;
}

/*
------------------------------------------------------------
Approach Summary:
------------------------------------------------------------

1. **BFS Approach**:
   - Use a queue for level-order traversal.
   - Track horizontal distance (HD) of each node.
   - For each HD, keep updating the value as new nodes are seen at deeper levels.
   - This way, the last node encountered at a HD will be the bottom-most one.

2. **DFS Approach**:
   - Traverse recursively (DFS), passing the current HD.
   - Always overwrite the value at each HD.
   - Final map will store the bottom-most node for each HD.

------------------------------------------------------------
Time Complexity: O(N * log N)
------------------------------------------------------------
- O(N) for visiting each node
- O(log N) per insertion/update in `map` (balanced BST)

------------------------------------------------------------
Space Complexity: O(N)
------------------------------------------------------------
- Queue for BFS or recursion stack for DFS
- Map stores up to N horizontal distances in worst case

------------------------------------------------------------
*/
