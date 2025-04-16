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

/*
other clear recursion

TreeNode* insertIntoBST(TreeNode* root, int val) {
    // Base case: If the current node is null, insert the new value here
    if (root == nullptr) {
        return new TreeNode(val);
    }

    // If value is less than current node's value, insert into left subtree
    if (val < root->val) {
        // If left child is null, insert directly
        if (root->left == nullptr) {
            root->left = new TreeNode(val);
        } else {
            // Else, continue recursion into left subtree
            insertIntoBST(root->left, val);
        }
    }
    // If value is greater or equal, insert into right subtree
    else {
        // If right child is null, insert directly
        if (root->right == nullptr) {
            root->right = new TreeNode(val);
        } else {
            // Else, continue recursion into right subtree
            insertIntoBST(root->right, val);
        }
    }

    // Return the unchanged root node
    return root;
}
*/
};
