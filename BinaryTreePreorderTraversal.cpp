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
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root)
            return {};

        stack<TreeNode*> st;         // Stack to store nodes
        vector<int> ans;             // Result vector

        st.push(root);               // Start with root node

        while (!st.empty()) {
            TreeNode* cur = st.top(); st.pop();  // Visit node
            ans.push_back(cur->val);             // Add to result

            // Push right child first so that left is processed first
            if (cur->right)
                st.push(cur->right);
            if (cur->left)
                st.push(cur->left);
        }

        return ans;
    }
};
/*

// using recursion

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        preorder(root, ans);
        return ans;
    }

    void preorder(TreeNode* root, vector<int>& ans) {
        if (!root)
            return;
        ans.push_back(root->val);        // Visit root
        preorder(root->left, ans);       // Visit left subtree
        preorder(root->right, ans);      // Visit right subtree
    }
};

*/
