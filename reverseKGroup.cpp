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

// iterative
class Solution {
public:
    ListNode* reverseOneGroup(ListNode* head_prev, ListNode* tail_next){
        //head_prev: the node before current group's head
        //tail_prev: the node after current group's tail
        ListNode* cur = head_prev->next;
        ListNode* new_head_prev = cur;
        ListNode* prev = head_prev;
        ListNode* next;

        while(cur != tail_next){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        head_prev->next = prev;
        new_head_prev->next = cur;
        
        return new_head_prev;
    };
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || !head->next || k == 1) return head;
        
        ListNode* dummy_head = new ListNode(-1);
        dummy_head->next = head;
        ListNode* group_head_prev = dummy_head;
        
        for(int i = 1; head; ++i){
            if(i%k == 0){
                group_head_prev = reverseOneGroup(group_head_prev, head->next);
                head = group_head_prev->next;
            }else{
                head = head->next;
            }
        }
        
        return dummy_head->next;
    }
};
// recursive
//
// class Solution {
// public:
// int length(ListNode * node){
//     int count=0;
//     while(node){
//         count++;
//         node=node->next;
//     }
//     return count;
// }
// ListNode* reverseKGroup(ListNode* head, int k) {
//    if(length(head) < k)return head;
//    ListNode* cur=head;
//    ListNode* prev=NULL, *next=NULL;
//    for(int i=0; i < k; i++){
//        next=cur->next;
//        cur->next=prev;
//        prev=cur;
//        cur=next;
//    }
//    head->next=reverseKGroup(cur, k);
//    return prev;
//  }
// };

//https://leetcode.com/problems/reverse-nodes-in-k-group/
