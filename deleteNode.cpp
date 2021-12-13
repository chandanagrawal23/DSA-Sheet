/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//https://leetcode.com/problems/delete-node-in-a-linked-list/
class Solution {
public:
    void deleteNode(ListNode* node) {
/*       *(node) = *(node->next);
OR
*/        
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
