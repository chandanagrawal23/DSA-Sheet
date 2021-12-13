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
#define ull unsigned long long
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root==NULL)return 0;
        pair<TreeNode*,ull>pr(root,0);
        queue<pair<TreeNode*,ull>>q;
        q.push(pr);
        ull mx=0;
        while(q.size()>0)
        {
            ull size=q.size();
            ull lm=q.front().second;
            ull rm=q.front().second;
            while(size--)
            {
                pair<TreeNode*,ull>temp=q.front();
                q.pop();
                rm=temp.second;
                if(temp.first->left)q.push({temp.first->left,temp.second*2+1});
                if(temp.first->right)q.push({temp.first->right,temp.second*2+2});
            }
            mx=max(mx,rm-lm+1);
        }
        return (int)mx;
    }
};
//https://leetcode.com/problems/maximum-width-of-binary-tree/

/*

            1(1)
          /   \
         2(2)  3(3)
        / \   /   \
    4(4)   X  X   5(7)
  
  
left child is 2*i , right child is 2*i +1
for each level find first and last node , and just subtract its node number 

for 3rd level answer is 7-4+1 which is 4
*/
