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
// https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/
class Solution {
public:
    int sumEvenGrandparent(TreeNode* root) {
        int sum = 0;
        queue<TreeNode*> q;
        q.push(root);
        
        //LevelOrderTraversal
        while(!q.empty()) {
            TreeNode* node = q.front();q.pop();
            if(node->left != NULL) {
                q.push(node->left);
                if(node->val % 2 == 0) {
                    if(node->left->left != NULL) {
                        sum += node->left->left->val;
                    }
                    if(node->left->right != NULL) {
                        sum += node->left->right->val;
                    }
                }
            }

            if(node->right != NULL) {
                q.push(node->right);
                if(node->val % 2 == 0) {
                    if(node->right->left != NULL) {
                        sum += node->right->left->val;
                    }
                    if(node->right->right != NULL) {
                        sum += node->right->right->val;
                    }
                }
            }
        }
        
        return sum;
    }
};
