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
    // Function to invert a binary tree (mirror the tree)
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root; // Base case: if tree is empty, return null

        queue<TreeNode*> q;
        q.push(root); // Start with the root node

        while (!q.empty()) {
            TreeNode* current = q.front(); q.pop();

            // Swap left and right children
            swap(current->left, current->right);

            // Add children to the queue for further processing
            if (current->left) 
                q.push(current->left);
            if (current->right) 
                q.push(current->right);
        }

        return root; // Return the root of the inverted tree
    }
};


/*

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // Base case: if tree is empty, return null
        if (!root) return nullptr;

        // Recursively invert left and right subtrees
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // Swap the left and right children
        root->left = right;
        root->right = left;

        return root; // Return the root of the inverted subtree
    }
};




*/
