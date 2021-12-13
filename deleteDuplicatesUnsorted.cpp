/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        ListNode* prev = new ListNode(-1);  // to keep track of last node that occured only once
        ListNode* ans = prev;  // to represent our final list
        ListNode* curr = head;
        unordered_map<int,int> M;  // to store values with their count
        while(curr != NULL) {
            M[curr->val]++;
            curr = curr->next;
        }
        
        curr = head;
        
        while(curr != NULL) {
            if(M[curr->val] > 1) {  // if value is found more than once
                curr = curr->next;  // find next node with count == 1
            } else {
                prev->next = curr;  //  assigning current unique node to the next of last unique node
                prev = curr;  // current node becomes last uniquely occuring node
                curr = curr->next;
            }
        }
        prev->next = NULL;  // set null to the last of our list of unique value nodes
        return ans->next;  // return the list 
    }
};

//https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/
