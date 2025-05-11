class Solution {
public:
    // Main function to convert sorted linked list to BST.
    TreeNode *sortedListToBST(ListNode *head)
    {
        return sortedListToBST(head, NULL); // Call helper function with initial tail as NULL.
    }
    
private:
    // Helper function to recursively construct BST from sorted linked list.
    TreeNode *sortedListToBST(ListNode *head, ListNode *tail)
    {
        if (head == tail) // Base case: no more nodes in the range.
            return NULL;
            
        // Only one node remaining in the range.
        if (head->next == tail) 
        { 
            TreeNode *root = new TreeNode(head->val); // Create leaf node.
            return root;
        }
        
        // Use two pointers to find the middle node (root of the BST).
        ListNode *mid = head, *fast = head;
        while (fast != tail && fast->next != tail) 
        {  
            mid = mid->next; // Move mid to the next node.
            fast = fast->next->next; // Move fast by two steps.
        }
        
        // Create root node with the middle value.
        TreeNode *root = new TreeNode(mid->val);
        
        // Recursively build left and right subtrees.
        root->left = sortedListToBST(head, mid); // Left subtree.
        root->right = sortedListToBST(mid->next, tail); // Right subtree.
        
        return root; // Return the constructed BST.
    }
};
