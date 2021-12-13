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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* node = head, *offsetNode = head;
        for (int i = 0; i < n; ++i)
            node = node->next;
        // cout<<node->val<<" ";

        // if node is NULL n is equal to the length of the linked list and we have to remove the head
        if (node == NULL)
            return head->next;

        while (node->next != NULL) {
            node = node->next;
            offsetNode = offsetNode->next;
        }
        
        // cout<<offsetNode->val<<" ";

        offsetNode->next = offsetNode->next->next;

        return head;
    }
};
