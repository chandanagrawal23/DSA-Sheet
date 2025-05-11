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
    int sumRootToLeaf(TreeNode* root, int val = 0) {
        if (!root) 
            return 0;  // If the current node is null, return 0 (no value to add)
        
        val = val * 2 + root->val;  // Update the value by shifting left (val*2) and adding root's value
        // or val = val<<1 + root->val;
        
        if (root->left == NULL && root->right == NULL) 
            return val;  // If it's a leaf node, return the current value
        
        // Recursively sum values for left and right subtrees
        return sumRootToLeaf(root->left, val) + sumRootToLeaf(root->right, val);
    }
};
