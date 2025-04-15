/*

Approach 1: Using Stack
Time Complexity: O(n), where n is the length of the linked list. Space Complexity: O(n), due to the stack used to store the list nodes.
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // Stack to store all node values
        stack<ListNode*> st;
        
        // Traverse the list and push each node into the stack
        ListNode* temp = head;
        while (temp) {
            st.push(temp);
            temp = temp->next;
        }
        
        // Traverse the list again and compare values with stack
        ListNode* t2 = head;
        while (t2) {
            ListNode* vali = st.top();
            if (vali->val != t2->val)  // If any value does not match, it's not a palindrome
                return false;
            st.pop();
            t2 = t2->next;
        }
        
        return true;
    }
};

/*
=========================================================================================================================
Approach 2: Reversing the Second Half of the List
Time Complexity: O(n), where n is the length of the linked list. Space Complexity: O(1), as we only use a constant amount of extra space.

Find the middle of the list using a slow and fast pointer approach.

Reverse the second half of the list.

Compare the first half with the reversed second half.

=========================================================================================================================

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Step 1: Find the middle of the list
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Step 2: Reverse the second half of the list
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        
        // Step 3: Compare the first and reversed second halves
        ListNode* firstHalf = head;
        ListNode* secondHalf = prev;
        while (secondHalf) {
            if (firstHalf->val != secondHalf->val)
                return false;
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        
        return true;
    }
};

===================================================================================================
Approach 3: Using a Recursive Method (With Two Pointers)
Time Complexity: O(n), where n is the length of the linked list. Space Complexity: O(n), due to recursion stack space.

In this approach, we recursively compare nodes while traveling down the linked list.

==============================================================================================================

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        return isPalindromeHelper(head, head);
    }

private:
    bool isPalindromeHelper(ListNode* left, ListNode*& right) {
        if (!right) return true;  // Base case: If right pointer has reached the end, we stop
        
        bool result = isPalindromeHelper(left, right->next); // Recursive call to the end
        
        if (!result) return false; // If any comparison failed, return false
        
        // Compare the current values of left and right pointers
        bool currentMatch = (left->val == right->val);
        
        left = left->next;  // Move the left pointer forward
        
        return currentMatch;  // Return whether the current nodes match
    }
};

==============================================================================================================
Approach 4: Using Fast and Slow Pointers to Find the Middle and Reverse
This approach is similar to Approach 2, but with a slight difference in implementation by using an additional pointer to track the head of the first half.

Find the middle using slow and fast pointers.

Reverse the second half.

Compare the first and second halves.

==============================================================================================================

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Find the middle of the linked list
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse the second half of the list starting from slow
        ListNode* prev = nullptr;
        while (slow) {
            ListNode* temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }
        
        // Compare the first and second halves
        ListNode* left = head;
        ListNode* right = prev;
        while (right) {
            if (left->val != right->val) return false;
            left = left->next;
            right = right->next;
        }
        
        return true;
    }
};



*/
