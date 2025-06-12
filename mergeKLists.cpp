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

// Custom comparator for min-heap (priority queue)
struct cmp
{
    bool operator()(ListNode* x1, ListNode* x2)
    {
        return x1->val > x2->val;
    }
};

class Solution 
{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        // Min-heap to store the heads of each list
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;

        // Push the first node of each list into the heap
        for (int i = 0; i < lists.size(); i++) 
        {
            if (lists[i]) 
            {
                pq.push(lists[i]);
            }
        }

        // Dummy node to help build the result list
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;

        // Build the merged list
        while (!pq.empty()) 
        {
            ListNode* temp = pq.top();
            pq.pop();
            head->next = temp;

            if (temp->next) 
            {
                pq.push(temp->next);
            }

            head = head->next;
        }

        return dummy->next;
    }
};

/*
Approach:
- Use a min-heap to always get the node with the smallest value.
- Push the first node of each list to the heap.
- Keep extracting the min and pushing its next node.

Time: O(N log K), where N = total nodes, K = number of lists.
Space: O(K), for the heap.
*/

//=====================================================================================================================

// if you do not want to use struct cmp then u can use touple 

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

class Solution 
{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        // Min-heap with tuple: (node value, index, node pointer)
        priority_queue<tuple<int, int, ListNode*>, 
                       vector<tuple<int, int, ListNode*>>, 
                       greater<>> pq;

        // Push first node of each list with index (to avoid tie-breaking issues)
        for (int i = 0; i < lists.size(); ++i) 
        {
            if (lists[i]) 
            {
                pq.emplace(lists[i]->val, i, lists[i]);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;

        // Merge lists
        while (!pq.empty()) 
        {
            auto [val, idx, node] = pq.top();
            pq.pop();

            head->next = node;
            head = head->next;

            if (node->next) 
            {
                pq.emplace(node->next->val, idx, node->next);
            }
        }

        return dummy->next;
    }
};

/*
Approach:
- Use a min-heap of (value, index, node*) to avoid pointer comparison issues.
- Always extract the node with smallest value and push its next if exists.

Time: O(N log K), where N = total nodes, K = number of lists
Space: O(K), heap stores one node per list at a time
*/

