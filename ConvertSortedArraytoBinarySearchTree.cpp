/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Helper function to recursively build the binary search tree (BST)
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end){
        // Base case: If the range is invalid (start >= end), return NULL
        if (end <= start) return NULL; 
        
        // Find the middle index of the current range
        int midIdx = (start + end ) / 2;
        
        // Create a new node with the value at the middle index
        TreeNode* root = new TreeNode(nums[midIdx]);
        
        // Recursively build the left subtree from the left half of the array
        root->left = sortedArrayToBST(nums, start, midIdx);
        
        // Recursively build the right subtree from the right half of the array
        root->right = sortedArrayToBST(nums, midIdx + 1, end);
        
        // Return the root of the current subtree
        return root;
    }

public:
    // Main function to convert the sorted array to a balanced binary search tree (BST)
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // Call the helper function with the initial range (start = 0, end = size of the array)
        return sortedArrayToBST(nums, 0, nums.size());
    }
};
