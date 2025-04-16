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
    // Main function to be called
    int sumNumbers(TreeNode* root) 
    {
        if (root == nullptr)
            return 0;  // Edge case: empty tree
        return recur(root, 0); // Start recursion with initial sum as 0
    }

    // Helper recursive function to build numbers from root to leaf
    int recur(TreeNode* root, int sum) 
    {
        if (root == NULL)
            return 0;

        // Add current node's value to the path number
        sum = sum * 10 + root->val;

        // If it's a leaf node, return the number formed so far
        if (root->left == NULL && root->right == NULL)
            return sum;

        // Recursively compute sum from left and right subtrees
        int leftSum = recur(root->left, sum);
        int rightSum = recur(root->right, sum);

        // Return total sum from both subtrees
        return leftSum + rightSum;
    }
};
