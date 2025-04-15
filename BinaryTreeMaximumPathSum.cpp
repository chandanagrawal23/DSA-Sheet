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
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;  // Initialize answer to minimum possible
        recursion(root, ans);  // Start recursion to find max path sum
        return ans;  // Return the result
    }

    int recursion(TreeNode* root, int &ans) {
        if (!root) return 0;  // If node is null, return 0
        
        // Get the max path sum for left and right child nodes, ensuring non-negative sums
        int l = max(recursion(root->left, ans), 0);
        int r = max(recursion(root->right, ans), 0);
        
        // Calculate new path sum including the current node and both children
        // assume like a inverted V ( in lambda)
        int new_price = root->val + l + r; 

        ans = max(ans, new_price);  // Update the max path sum if needed
        
        // assume like the left stick of lamda or right stick of lambda
        return root->val + max(l, r);  // Return the max sum for the current node
    }
};
