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
 //https://leetcode.com/problems/average-of-levels-in-binary-tree/
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*>pq;
        pq.push(root);
        vector<double>vc;
        while(!pq.empty())
        {
            int n = pq.size();
            double sum = 0.0;
            for(int i=0;i<n;i++)
            {
                TreeNode* tp = pq.front();pq.pop();
                sum += tp->val;
                if(tp->left)
                    pq.push(tp->left);
                if(tp->right)
                    pq.push(tp->right);
            }
            vc.push_back(sum/(1.00000*n));
        }
        return vc;
    }
};
