/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
    //     queue<Node*> q;
    //     if(!root) return NULL;
    //     q.push(root);
    //     while(q.empty()==false){
    //         Node* temp = q.front();
    //         int n = q.size();
    //         for(int i=0;i<n;i++){
    //             Node* popped = q.front();
    //             q.pop();
    //             if(i>0){
    //                 temp->next = popped;
    //                 temp = temp->next;
    //             }
    //             if(popped->left)
    //                  q.push(popped->left);
    //             if(popped->right)
    //                  q.push(popped->right);
    //         }
    //     }
    //     return root;
    // }
        if (!root) return NULL;
        Node* pre = root;
        while(pre->left) {
            Node* cur = pre;
            while(cur)
                {
                cur->left->next = cur->right;
                if(cur->next)
                        cur->right->next = cur->next->left;
                cur = cur->next;
            }
            pre = pre->left;
        }
            return root;
        }
};
