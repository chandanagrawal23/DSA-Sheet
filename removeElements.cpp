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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* prev = nullptr, *cur = head;
        while(cur) {
            if(cur->val == val) {
                if(cur == head)
                    head = head->next;
                else
                    prev->next = cur->next;
            }
            else {
                prev = cur;
            }
            cur = cur->next;
        }
        return head;
    }
};
