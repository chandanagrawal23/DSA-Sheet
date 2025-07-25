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
    // -----------------------------------------------------
    // TOP VIEW USING BFS
    // -----------------------------------------------------
    // Idea:
    // - Perform level order traversal (BFS).
    // - Keep track of horizontal distance (HD) of each node from root.
    // - Root has HD = 0, left child = HD - 1, right child = HD + 1.
    // - For each HD, store the **first node** encountered during BFS
    //   (this ensures topmost node for that vertical column is stored).
    // - Use a map<int, int> to store HD -> node value mapping.
    // - Finally, return node values in order from leftmost HD to rightmost HD.
    // -----------------------------------------------------
    vector<int> topView(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        queue<pair<TreeNode*, int>> q;      // {node, HD}
        map<int, int> hdMap;                // HD -> first seen node

        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            if (hdMap.find(hd) == hdMap.end())  // topmost at this HD
                hdMap[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        for (auto& [hd, val] : hdMap)  // collect in left-to-right order
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

/*
------------------------------------------------------------
Approach Summary:
------------------------------------------------------------
- Use BFS traversal to ensure topmost (first seen) nodes at each horizontal distance (HD) are captured.
- Track HD of each node starting from root (HD = 0), left = -1, right = +1.
- Use map<int, int> to store first node for each HD during traversal.
- At the end, extract node values from map in order of increasing HD.

------------------------------------------------------------
Time Complexity: O(N * log N)
------------------------------------------------------------
- Each node is visited once => O(N)
- Insertion into map takes O(log N) per node (due to red-black tree)

------------------------------------------------------------
Space Complexity: O(N)
------------------------------------------------------------
- Queue can store up to O(N) nodes in worst case (level with max width)
- Map stores up to O(N) entries (each HD at most once)
------------------------------------------------------------
*/
