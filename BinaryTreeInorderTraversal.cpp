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
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st; // Stack to simulate recursion
        TreeNode* cur = root;
        vector<int> ans; // Result vector to store inorder traversal

        while (cur || !st.empty()) {
            // Go to the leftmost node
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }

            // Process the top node
            cur = st.top(); st.pop();
            ans.push_back(cur->val); // Add current node's value

            // Now visit the right subtree
            cur = cur->right;
        }
        return ans;
    }
};

/* 
// Recursive approach for inorder traversal

class Solution {
public:
    vector<int> ans;

    vector<int> inorderTraversal(TreeNode* root) {
        if (root == NULL)
            return ans;
        inorderTraversal(root->left); // Visit left subtree
        ans.push_back(root->val);     // Visit root
        inorderTraversal(root->right); // Visit right subtree
        return ans;
    }
};

*/
