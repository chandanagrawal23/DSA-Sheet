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
 //https://leetcode.com/problems/same-tree/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode*>pp, qq;
        pp.push(p);
        qq.push(q);
        while(!pp.empty() && !qq.empty()) {
            auto a = pp.front();
            pp.pop();
            auto b = qq.front();
            qq.pop();
            if(!a and !b)
                continue;
            if(!a || !b)
                return false;
            if (a->val != b->val) {
                return false;
            }
            
            pp.push(a->left);
            pp.push(a->right);
            
            qq.push(b->left);
            qq.push(b->right);
        }
        return true;
    }
};

/*

class Solution {
public:

    // Function to check if two binary trees are the same
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // If both nodes are null, trees are identical at this position
        if (!p && !q)
            return true;
        // If one of the nodes is null, trees are different
        if (!p || !q)
            return false;
        // Check current node values and recursively check left and right subtrees
        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

*/
