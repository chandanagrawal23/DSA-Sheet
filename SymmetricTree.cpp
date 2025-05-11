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
    // Main function to check if a binary tree is symmetric
    bool isSymmetric(TreeNode* root) {
        if (!root) return true; // An empty tree is symmetric
        return judge(root->left, root->right); // Compare left and right subtrees
    }

    // Helper function to compare two subtrees
    bool judge(TreeNode* l, TreeNode* r) {
        if (!l && !r) // Both subtrees are empty
            return true;
        if (!l || !r) // One subtree is empty, the other is not
            return false;
        // Values must match and mirrored subtrees must also be symmetric
        return l->val == r->val && judge(l->right, r->left) && judge(l->left, r->right);
    }

    /*
    // Iterative approach using two queues
    bool isSymmetric(TreeNode* root) {
        if (!root)
            return true;
        queue<TreeNode*> fromleft, fromright;
        fromleft.push(root);
        fromright.push(root);
        while (!fromleft.empty() || !fromright.empty()) {
            TreeNode* lefti = fromleft.front(); fromleft.pop();
            TreeNode* righti = fromright.front(); fromright.pop();
            if (!lefti && !righti)
                continue;
            if (!lefti || !righti)
                return false;
            if (lefti->val != righti->val)
                return false;
            // Push children in opposite order to compare mirror structure
            fromleft.push(lefti->left);
            fromleft.push(lefti->right);
            fromright.push(righti->right);
            fromright.push(righti->left);
        }
        return true;
    }
    */
};
