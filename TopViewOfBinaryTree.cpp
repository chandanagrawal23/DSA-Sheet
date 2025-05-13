#include <bits/stdc++.h>
using namespace std;

// -------------------------------
// Definition of TreeNode
// -------------------------------
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// -------------------------------
// Solution Class with Top View
// -------------------------------
class Solution
{
public:
    // ------------------------------
    // TOP VIEW USING BFS
    // ------------------------------
    vector<int> topView(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        // Queue for BFS: pair of node and horizontal distance
        queue<pair<TreeNode*, int>> q;
        // Map to store first node at each horizontal distance
        map<int, int> hdMap;

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // Insert only if not already present (top-most)
            if (hdMap.find(hd) == hdMap.end())
                hdMap[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        // Collect results from leftmost to rightmost HD
        for (auto& [hd, val] : hdMap)
            result.push_back(val);

        return result;
    }
};

// -------------------------------
// Main function to test the solution
// -------------------------------
int main()
{
    /*
         Constructing the following tree:
                1
               / \
              2   3
               \   \
                4   5
               /     \
              6       7

        Top View: 2 1 3 5 7
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    Solution sol;
    vector<int> top = sol.topView(root);

    cout << "Top View: ";
    for (int x : top) cout << x << " ";
    cout << endl;

    return 0;
}
