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
    int countNodes(TreeNode* root) {
        // Base case: if the tree is empty, return 0
        if (!root) return 0;

        int leftHeight = 0, rightHeight = 0;

        TreeNode *l = root, *r = root;

        // Calculate the height of the leftmost path
        while (l)
        {
            leftHeight++;
            l = l->left;
        }

        // Calculate the height of the rightmost path
        while (r)
        {
            rightHeight++;
            r = r->right;
        }

        // If both heights are equal, it's a perfect binary tree
        // Total number of nodes = 2^height - 1
        if (leftHeight == rightHeight)
            return ((1 << leftHeight) - 1);

        // Otherwise, recursively count nodes in left and right subtrees
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
