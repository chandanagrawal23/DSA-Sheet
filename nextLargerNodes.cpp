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
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> result;
	stack<pair<int,int> > st;
	for (int i = 0; head; head = head->next) {
		while (st.size() && head->val > st.top().first) {
			result[st.top().second] = head->val;
			st.pop();
		}
		st.push({head->val, i++});
		result.push_back(0);
	}
	return result;
    }
};
