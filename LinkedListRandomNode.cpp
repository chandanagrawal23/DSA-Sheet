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
    vector<int> list;  // Vector to store the values from the linked list
    int size;          // Variable to store the size of the linked list
    
    // Constructor to initialize the Solution object
    // Traverse the linked list and store the values in the list vector
    Solution(ListNode* head) {
        while (head) {
            list.push_back(head->val);  // Store the current node value in the list
            head = head->next;          // Move to the next node
        }
        size = list.size();  // Set the size of the list
    }
    
    // Method to return a random node value from the linked list
    int getRandom() {
        // Generate a random index between 0 and size-1
        int i = rand() % size;
        return list[i];  // Return the value at the random index
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
