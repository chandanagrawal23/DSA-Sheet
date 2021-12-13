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

// https://leetcode.com/problems/reverse-linked-list/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // ListNode* cur = NULL;
        // while (head) {
        //     ListNode* next = head -> next;
        //     head -> next = cur;
        //     cur = head;
        //     head = next;
        // }
        // return cur;
        ListNode* prev = NULL;
        ListNode* curr = head;
        
        while(head)
        {
            curr = head;
            head = head->next;
            curr->next = prev;
            prev = curr;
        }
        return prev;
    }
};

/*
ListNode* reverseList(ListNode* head) {
        if (!head || !(head -> next)) {
            return head;
        }
        ListNode* node = reverseList(head -> next);
        head -> next -> next = head;
        head -> next = NULL;
        return node;
    }
    

*/
