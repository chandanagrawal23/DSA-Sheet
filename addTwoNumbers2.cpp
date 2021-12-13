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
//https://leetcode.com/problems/add-two-numbers-ii/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1 = 0 , len2 = 0 ;
        ListNode* curr1 = l1;
         // find the length of both lists
        while(curr1)
        {
            curr1 = curr1->next;
            len1++;
        }
        ListNode* curr2 = l2;
        while(curr2)
        {
            curr2 = curr2->next;
            len2++;
        }
        // parse both lists
        // and sum the corresponding positions 
        // without taking carry into account
        // 3->3->3 
        //  + 7->7 --> 3->10->10--> 10->10->3
        curr1 = l1 , curr2 = l2;
        
        ListNode* head = NULL;
        
        while(len1 and len2)
        {
            int val = 0;
            if(len1>=len2)
            {
                val += curr1->val;
                curr1 = curr1->next;
                len1--;
            }
            if(len1<len2)
            {
                val += curr2->val;
                curr2 = curr2->next;
                len2--;
            }
              // update the result: add to front
            ListNode* curr = new ListNode(val);
            curr->next = head;
            head = curr;
        }
        
        curr1 = head;
        head = NULL;
        int carry = 0;
        // take the carry into account
        // to have all elements to be less than 10
        // 10->10->3 --> 0->1->4 --> 4->1->0
        while (curr1) {
            // current sum and carry
            int val = (curr1->val + carry) % 10;
            carry = (curr1->val + carry) / 10;
            
            // update the result: add to front
            ListNode* curr = new ListNode(val);
            curr->next = head;
            head = curr;

            // move to the next elements in the list
            curr1 = curr1->next;    
        }
        // add the last carry
        if (carry != 0) {
                ListNode* curr = new ListNode(carry);
                curr->next = head;
                head = curr;    
            }

        return head;
    }
};
