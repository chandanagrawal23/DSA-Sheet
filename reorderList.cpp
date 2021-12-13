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

//https://leetcode.com/problems/reorder-list/
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast and fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout<<slow->val<<"\n";
        
        // 1 2 3 4 5 6 => 1 2 3 ,  4 5 6
        
        ListNode* rightHalf = slow;
        ListNode* prev = NULL;
        ListNode* curr = rightHalf;
        // 4 5 6 => 6 5 4
        while(rightHalf)
        {
            curr = rightHalf;
            rightHalf = rightHalf->next;
            curr->next = prev;
            prev = curr;
        }

        // now join 
        // 1 2 3 , 6 5 4 => 1 6 2 5 3 4
        ListNode* first = head;
        ListNode* second = prev;
        while (second->next) {
          ListNode* tmp = first->next;
          first->next = second;
          first = tmp;

          tmp = second->next;
          second->next = first;
          second = tmp;
        }
    }
};


/*

without extra space -

reverse right half (using slow and fast)

and then pair-

1 2 3 4 5 6
1 2 3  , , 6 5 4

1 6 2 5 3 4

*/
