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
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root)
            return {};

        vector<int> ans;
        stack<TreeNode*> st;

        st.push(root);

        while (!st.empty()) {
            TreeNode* cur = st.top(); st.pop();
            ans.push_back(cur->val);

            // Push left first, then right (reverse of actual postorder)
            if (cur->left)
                st.push(cur->left);
            if (cur->right)
                st.push(cur->right);
        }

        reverse(ans.begin(), ans.end()); // Reverse to get correct postorder
        return ans;
    }
};
/*

// Recursive 

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        postOrder(root, ans);
        return ans;
    }

    void postOrder(TreeNode* root, vector<int>& ans) {
        if (!root)
            return;
        postOrder(root->left, ans);     // Traverse left subtree
        postOrder(root->right, ans);    // Traverse right subtree
        ans.push_back(root->val);       // Visit root
    }
};

*/
