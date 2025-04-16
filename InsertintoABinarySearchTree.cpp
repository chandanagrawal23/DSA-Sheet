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
/*
 // RECURSIVE
	TreeNode* insertIntoBST(TreeNode *node, int val) {
		if (!node) {
			TreeNode *newNode = new TreeNode(val);
			return newNode;
		}
		if (val < node->val) {
			node->left = insertIntoBST(node->left, val);
		}
		else {
			node->right = insertIntoBST(node->right, val);
		}
		return node;
	}
*/
 // ITERATIVE
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode *prev, *cur;      
        prev= cur = root;
        TreeNode *node = new TreeNode(val);
        if(root == NULL)
            return node;
        while(cur)
        {
            if(val < cur->val)      // if val is less than curr node, move left side
            {
                prev = cur;
                cur = cur->left;
            }
            else if(val > cur->val) //if val is greater than curr node, move right side
            {
                prev = cur;
                cur = cur->right;
            }
        }
        if(val < prev->val)         //simply attach value to last node
            prev->left = node;
        else
            prev->right = node;
        return root;
    }
};
