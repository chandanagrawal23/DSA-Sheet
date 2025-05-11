class Solution {
public:
    // Main function to build the tree from preorder and inorder traversals.
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        int rootIdx = 0; // Initialize the root index for preorder.
        return build(preorder, inorder, rootIdx, 0, inorder.size() - 1); // Call helper function to construct the tree.
    }
    
    // Helper function to recursively build the tree.
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int& rootIdx, int left, int right)
    {
        if (left > right) 
            return NULL; // Base case: no nodes in the current range.
        
        // Find the root index in the inorder array (pivot).
        int pivot = left;
        while (inorder[pivot] != preorder[rootIdx]) 
            pivot++;  // Search for the root element in inorder.
        
        rootIdx++; // Move to the next element in preorder (the next root).
        
        // Create a new tree node with the value found at pivot in inorder.
        TreeNode* newNode = new TreeNode(inorder[pivot]);
        
        // Recursively build the left and right subtrees.
        newNode->left = build(preorder, inorder, rootIdx, left, pivot - 1);  // Left subtree.
        
        newNode->right = build(preorder, inorder, rootIdx, pivot + 1, right); // Right subtree.
        
        return newNode; // Return the newly created node.
    }
};
