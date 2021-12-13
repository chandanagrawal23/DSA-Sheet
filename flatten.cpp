/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        Node* temp = head;
        while(temp)
        {
            if(temp->child)
            {
                Node* nextNode = temp->next;
                temp->next = temp->child;
                temp->next->prev = temp;
                temp->child = NULL;
                Node* newTemp = temp->next;
                
                while(newTemp->next)
                    newTemp = newTemp->next;
                
                newTemp->next = nextNode;
                
                if(nextNode)
                    nextNode->prev = newTemp;
                
            }
            temp = temp->next;
        }
        
        return head;
        
    }
};
//https://github.com/chandanagrawal23/DSA-Sheet/blob/main/removeNthFromEnd.cpp
