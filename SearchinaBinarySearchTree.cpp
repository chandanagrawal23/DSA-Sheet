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
    // Function to search for a value in a Binary Search Tree (BST)
    TreeNode* searchBST(TreeNode* root, int val) {
        // If root is NULL, return NULL
        if (!root)
            return NULL;
        
        // If the value matches the current node, return the node
        if (root->val == val)
            return root;
        
        // If the value is greater, search in the right subtree
        if (root->val < val)
            return searchBST(root->right, val);
        
        // If the value is smaller, search in the left subtree
        else
            return searchBST(root->left, val);
    }
};
