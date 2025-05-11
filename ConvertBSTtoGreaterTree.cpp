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
private:
    int cur_sum = 0; // Running sum of node values.
public:
    // Perform reverse in-order traversal.
    void travel(TreeNode* root) {
        if (!root) return; // Base case: null node.
        
        if (root->right) 
          travel(root->right); // Traverse right subtree first.

        root->val = (cur_sum += root->val); // Update current node's value.
        
        if (root->left) 
          travel(root->left); // Traverse left subtree.
    }

    // Start conversion of BST to greater tree.
    TreeNode* convertBST(TreeNode* root) {
        travel(root); // Perform the traversal and update tree.
        return root; // Return the modified tree.
    }
};
