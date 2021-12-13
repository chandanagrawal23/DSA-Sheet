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
//https://leetcode.com/problems/add-two-numbers/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* crhead = dummy;
        int carry =0;
        int val=0;
        while(l1 or l2 or carry )
        {
            val =0;
            if(l1)
                val += l1->val , l1=l1->next;
            if(l2)
                val += l2->val , l2=l2->next;
            if(carry)
                val += carry;
            carry = val/10;
            val%=10;
            ListNode* temp = new ListNode(val);
            crhead->next = temp;
            crhead = crhead->next;
        }
        return dummy->next;
    }
};
