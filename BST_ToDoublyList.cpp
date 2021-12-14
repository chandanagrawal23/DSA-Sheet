/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root)
            return NULL;
        Node* dummy = new Node(-1);
        Node* prev = dummy;
        Node* curr = root;
        stack<Node*>stk;
        while(curr || stk.empty()==false)
        {
            while(curr)
            {
                stk.push(curr);
                curr = curr->left;
            }
            curr = stk.top();stk.pop();
            curr->left = prev;
            prev->right = curr;
            prev = prev->right;
            curr = curr->right;
        }
        dummy->right->left = prev;
        prev->right = dummy->right;
        return dummy->right;
    }
};
//https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
