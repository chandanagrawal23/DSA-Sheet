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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // Create a queue to perform level order traversal
        queue<TreeNode*> pq;
        vector<vector<int>> ans;

        if (!root) {
            return ans;  // Return empty result if root is null
        }

        pq.push(root);  // Start with the root node

        while (!pq.empty()) {
            int n = pq.size();  // Get the number of nodes at the current level
            vector<int> vc;     // Temporary vector to store values of nodes at the current level

            for (int i = 0; i < n; i++) {
                TreeNode* tp = pq.front(); pq.pop();  // Pop the front node
                vc.push_back(tp->val);                 // Add the node value to the result for this level

                // Push left and right children if they exist
                if (tp->left) 
                    pq.push(tp->left);
                if (tp->right)
                    pq.push(tp->right);
            }
            ans.push_back(vc);  // Add current level result to final answer
        }
        return ans;  // Return the final level-order traversal result
    }
};
