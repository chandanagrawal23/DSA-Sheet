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
//https://leetcode.com/problems/binary-tree-right-side-view/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> view;
        queue<TreeNode*> todo;
        todo.push(root);
        while (!todo.empty()) {
            int n = todo.size();
            for (int i = 0; i < n; i++) {
                TreeNode* node = todo.front();
                todo.pop();
                if (i == n - 1) {
                    view.push_back(node -> val);
                }
                if (node -> left) {
                    todo.push(node -> left);
                }
                if (node -> right) {
                    todo.push(node -> right);
                }
            }
        }
        return view;
    }
};
