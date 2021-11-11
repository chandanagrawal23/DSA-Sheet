/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int>ans;
        if(root==NULL)
            return ans;
        stack<Node*> st;
        st.push(root);
        while(!st.empty())
        {
            Node *temp = st.top();st.pop();
            ans.push_back(temp->val);
            // first push right most then left ,  so at top we have left most child
            for(int i=temp->children.size()-1;i>=0;i--)
            {
                st.push(temp -> children[i]);
            }
        }
        return ans;
    }
};
