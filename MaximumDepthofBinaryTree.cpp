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
    int maxDepth(TreeNode* root) {
        // If the root is NULL, return depth as 0
        if (root == NULL)
            return 0;
        
        // If there's no left subtree, recurse on the right subtree
        if (!root->left)
            return 1 + maxDepth(root->right);

        // If there's no right subtree, recurse on the left subtree
        if (!root->right)
            return 1 + maxDepth(root->left);

        // Recursively calculate the maximum depth of both subtrees
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
/*

// ITERATIVE

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;  // If the tree is empty, return depth 0

        queue<TreeNode*> q;  // Queue to store nodes at each level
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            int levelSize = q.size();  // Number of nodes at the current level
            depth++;  // Increment depth for each level

            // Traverse all nodes at the current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();

                // Add left and right children to the queue if they exist
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return depth;  // Return the maximum depth
    }
};


*/
