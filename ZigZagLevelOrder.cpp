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

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*>pq;
        pq.push(root);
        vector<vector<int>>ans;
        if(!root)
            return ans;
        int f=0;
        int val = 0;
        while(!pq.empty())
        {
            int n = pq.size();
            vector<int>vc(n);
            for(int i=0;i<n;i++)
            {
                TreeNode* tp = pq.front();pq.pop();
                vc[f==0 ? i : n-i-1] = (tp->val);
                if(tp->left)
                        pq.push(tp->left);
                if(tp->right)
                        pq.push(tp->right);
               
            }
            f = 1-f;
            ans.push_back(vc);
        }
        return ans;
    }
};
