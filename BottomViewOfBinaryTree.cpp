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
    // ------------------------------
    // BOTTOM VIEW USING BFS
    // ------------------------------
    vector<int> bottomViewBFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        // Queue for BFS: pair of node and horizontal distance
        queue<pair<TreeNode*, int>> q;
        // Map to store the last node at each horizontal distance (bottom-most)
        map<int, int> hdMap;

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // Insert the current node, this will overwrite the previous one at the same HD
            hdMap[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        // Collect results from leftmost to rightmost HD
        for (auto& [hd, val] : hdMap)
            result.push_back(val);

        return result;
    }

    // Helper function for DFS traversal
    void dfs(TreeNode* node, int hd, map<int, int>& hdMap)
    {
        if (!node) return;

        // Update the map with the current node (this will overwrite any existing node at the same horizontal distance)
        hdMap[hd] = node->val;

        // Recursively visit left and right children with updated horizontal distance
        dfs(node->left, hd - 1, hdMap);
        dfs(node->right, hd + 1, hdMap);
    }

    // ------------------------------
    // BOTTOM VIEW USING DFS
    // ------------------------------
    vector<int> bottomViewDFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        map<int, int> hdMap;

        // Start DFS traversal from root at horizontal distance 0
        dfs(root, 0, hdMap);

        // Collect results from leftmost to rightmost HD
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

    // Test BFS approach
    vector<int> bottomBFS = sol.bottomViewBFS(root);
    cout << "Bottom View (BFS): ";
    for (int x : bottomBFS) cout << x << " ";
    cout << endl;

    // Test DFS approach
    vector<int> bottomDFS = sol.bottomViewDFS(root);
    cout << "Bottom View (DFS): ";
    for (int x : bottomDFS) cout << x << " ";
    cout << endl;

    return 0;
}
