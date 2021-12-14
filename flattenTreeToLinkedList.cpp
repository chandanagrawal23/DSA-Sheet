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
    // TreeNode* prev = NULL;
    // void flatten(TreeNode* root) {
    //     if (root == NULL)
    //         return;
    //     flatten(root->right);
    //     flatten(root->left);
    //     root->right = prev;
    //     root->left = NULL;
    //     prev = root;
    // }
    
    void flatten(TreeNode* root) {
        if (root == NULL) return;
        stack<TreeNode*>stk;
        stk.push(root);
        while (!stk.empty()){
         TreeNode* curr = stk.top();stk.pop();
            if (curr->right!=NULL)
                 stk.push(curr->right);
            if (curr->left!=NULL)
                 stk.push(curr->left);
            if (!stk.empty()) 
                 curr->right = stk.top();
            curr->left = NULL;//dont forget this!! 
        }
    }
};
//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
