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
    // Main function to find closest nodes for each query in q
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& q)
    {
        vector<vector<int>> res;
        vector<int> v;
        inOrder(root,v);  // In-order traversal to get the sorted values
        int n = v.size();
        
        // For each query, find the closest nodes
        for(int i = 0; i < q.size(); i++)
        {
            int mini = INT_MAX, maxi = INT_MIN;
            auto p = find(q[i], v, mini, maxi, n);  // Find closest nodes for query
            res.push_back(p);
        }
        return res;
    }

    // In-order traversal to fill the vector with node values
    void inOrder(TreeNode* root, vector<int> &v)
    {
        if(root == NULL) return;
        inOrder(root->left, v);   // Traverse left subtree
        v.push_back(root->val);   // Add node value to the vector
        inOrder(root->right, v);  // Traverse right subtree
    }

    // Binary search to find the closest nodes in the sorted vector v
    vector<int> find(int value, vector<int> &v, int mini, int maxi, int n)
    {
        int low = 0, high = n - 1;
        while(low <= high)
        {
            int mid = low + (high - low) / 2;
            if(v[mid] == value)
            {
                return {value, value};  // Found exact match
            }
            else if(v[mid] < value)
            {
                maxi = max(maxi, v[mid]);
                low = mid + 1;  // Move to right half
            }
            else
            {
                mini = min(mini, v[mid]);
                high = mid - 1;  // Move to left half
            }
        }
        
        // If no valid mini or maxi, set to -1
        if(mini == INT_MAX) mini = -1;
        if(maxi == INT_MIN) maxi = -1;
        
        return {maxi, mini};  // Return closest smaller and larger values
    }
};
