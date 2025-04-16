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
    unordered_map<int, int> subtreeSumFrequency;  // Maps each subtree sum to its frequency
    int highestFrequency = 0;                     // Tracks the highest frequency of any subtree sum

    vector<int> findFrequentTreeSum(TreeNode* root) {
        computeSubtreeSum(root);  // Perform post-order traversal to compute subtree sums

        vector<int> mostFrequentSums;
        // Collect all sums that occurred with the highest frequency
        for (const auto& [sum, freq] : subtreeSumFrequency) {
            if (freq == highestFrequency) {
                mostFrequentSums.push_back(sum);
            }
        }
        return mostFrequentSums;
    }

private:
    // Helper function to compute the sum of each subtree using post-order DFS
    int computeSubtreeSum(TreeNode* node) {
        if (node == nullptr) return 0;

        // Calculate sum of left and right subtrees plus current node's value
        int leftSum = computeSubtreeSum(node->left);
        int rightSum = computeSubtreeSum(node->right);
        int totalSum = leftSum + rightSum + node->val;

        // Record the frequency of this sum
        subtreeSumFrequency[totalSum]++;
        highestFrequency = max(highestFrequency, subtreeSumFrequency[totalSum]);

        return totalSum;  // Return this subtree's total sum to its parent
    }
};
