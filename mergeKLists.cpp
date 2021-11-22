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
// https://leetcode.com/problems/merge-k-sorted-lists/
struct cmp
{
    bool operator()(ListNode* x1 , ListNode* x2)
    {
        return x1->val>x2->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode* , vector<ListNode*> ,cmp>pq;
        for(int i=0;i<lists.size();i++)
        {
            if(lists[i])
                pq.push(lists[i]);
        }
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;
        while(!pq.empty())
        {
            ListNode* temp = pq.top();pq.pop();
            head->next = temp;
            if(temp->next)
                pq.push(temp->next);
            head = head->next;
        }
        return dummy->next;
    }
};
