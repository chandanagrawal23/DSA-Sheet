class Solution {
public:
    vector<int>ans;
    vector<int> preorderTraversal(TreeNode* root) {
        if(root==NULL)
            return ans;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty())
        {
            TreeNode* topNode = stk.top();stk.pop();
            ans.push_back(topNode->val);
            // push first Right Node
            if(topNode->right)
                stk.push(topNode->right);
            // then left node , so at top left node is there
            if(topNode->left)
                stk.push(topNode->left);
        }
        return ans;
    }
};
