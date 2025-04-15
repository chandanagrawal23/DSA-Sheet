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
    // Function to check if there is a path in the binary tree that sums up to the target
    bool hasPathSum(TreeNode* root, int targetSum) {
        // Base case: if root is NULL, no path exists
        if (root == NULL)
            return false;

        // If leaf node is reached, check if its value equals the remaining target sum
        if (root->left == NULL && root->right == NULL)
            return (root->val == targetSum);

        // Recursively check left and right subtrees with reduced target sum
        return (hasPathSum(root->left, targetSum - root->val)) || 
               (hasPathSum(root->right, targetSum - root->val));
    }
};
