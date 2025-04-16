class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> pq; // Queue for level order traversal (BFS)
        vector<vector<int>> ans; // Final result

        if (!root)
            return ans;

        pq.push(root);
        bool leftToRight = true; // Flag to indicate zigzag direction

        while (!pq.empty()) {
            int n = pq.size(); // Number of nodes at current level
            vector<int> level(n); // Vector to store current level's values

            for (int i = 0; i < n; ++i) {
                TreeNode* curr = pq.front();
                pq.pop();

                // Determine the position to insert value based on direction
                int index;
                if (leftToRight) {
                    index = i;
                } else {
                    index = n - 1 - i;
                }

                level[index] = curr->val;

                // Add children to the queue for next level
                if (curr->left)
                    pq.push(curr->left);
                if (curr->right)
                    pq.push(curr->right);
            }

            // Flip direction for next level
            leftToRight = !leftToRight;

            ans.push_back(level); // Add current level to result
        }

        return ans;
    }
};
