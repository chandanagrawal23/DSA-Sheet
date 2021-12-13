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
//https://leetcode.com/problems/remove-duplicates-from-sorted-list/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL)
            return head;
        ListNode* prev = head;
        ListNode* curr = head->next;
        while(curr){
            if(curr->val!=prev->val)
            {
                prev->next=curr;
                prev = curr;
            }
            curr = curr -> next;
        }
         prev->next = NULL; // bcz hame dekhna padega ki agar last me sare sae hai to ek hi occurence aaye
        return head;
    }
};
