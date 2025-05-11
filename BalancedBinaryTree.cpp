/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return dfs(root) != -1;  // If the tree is unbalanced, dfs will return -1
    }

    int dfs(TreeNode* root) {
        if (!root) return 0;  // Base case: if the node is NULL, return height 0

        int left = dfs(root->left);
        if (left == -1) return -1;  // If the left subtree is unbalanced, return -1

        int right = dfs(root->right);
        if (right == -1) return -1;  // If the right subtree is unbalanced, return -1

        // If the difference in heights is greater than 1, the tree is unbalanced
        if (abs(left - right) > 1) return -1;

        // Return the height of the current subtree
        return 1 + max(left, right);
    }
};
