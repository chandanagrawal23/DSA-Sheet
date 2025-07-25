// Approach 1 : Classic DFS
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
// Solution Class for Boundary Traversal
// -------------------------------
class Solution
{
public:
    // Helper: Check if a node is leaf
    bool isLeaf(TreeNode* node)
    {
        return !node->left && !node->right;
    }

    // Step 1: Add left boundary (excluding leaves)
    void addLeftBoundary(TreeNode* node, vector<int>& res)
    {
        TreeNode* curr = node->left;
        while (curr)
        {
            if (!isLeaf(curr)) res.push_back(curr->val);
            if (curr->left)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }

    // Step 2: Add all leaf nodes (in-order traversal)
    void addLeaves(TreeNode* node, vector<int>& res)
    {
        if (!node) return;
        if (isLeaf(node))
        {
            res.push_back(node->val);
            return;
        }
        addLeaves(node->left, res);
        addLeaves(node->right, res);
    }

    // Step 3: Add right boundary (excluding leaves) in bottom-up
    void addRightBoundary(TreeNode* node, vector<int>& res)
    {
        TreeNode* curr = node->right;
        vector<int> temp;

        while (curr)
        {
            if (!isLeaf(curr)) temp.push_back(curr->val);
            if (curr->right)
                curr = curr->right;
            else
                curr = curr->left;
        }

        // Add in reverse order
        reverse(temp.begin(), temp.end());
        res.insert(res.end(), temp.begin(), temp.end());
    }

    // Main function for boundary traversal
    vector<int> boundaryTraversal(TreeNode* root)
    {
        vector<int> res;
        if (!root) return res;
        if (!isLeaf(root)) res.push_back(root->val); // root only if not leaf

        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);

        return res;
    }
};

// -------------------------------
// Main to test the solution
// -------------------------------
int main()
{
    /*
         Constructing the following tree:
                1
              /   \
             2     3
            / \     \
           4   5     6
              / \   /
             7   8 9

        Boundary: 1 2 4 7 8 9 6 3
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(8);
    root->right->right = new TreeNode(6);
    root->right->right->left = new TreeNode(9);

    Solution sol;
    vector<int> boundary = sol.boundaryTraversal(root);

    cout << "Boundary Traversal: ";
    for (int x : boundary) cout << x << " ";
    cout << endl;

    return 0;
}

/*
------------------------------------------------------------
Approach Summary:
------------------------------------------------------------

Boundary traversal = left boundary + leaves + right boundary
(in anti-clockwise direction)

1. "Left Boundary":
   - Traverse from root->left.
   - Add nodes that are NOT leaves.

2. "Leaf Nodes":
   - Use DFS (in-order style).
   - Add all leaves from left to right.

3. "Right Boundary":
   - Traverse from root->right.
   - Add nodes that are NOT leaves in bottom-up order.

Edge Case:
- If root is a leaf, we skip adding it initially but handle it in leaf traversal.

------------------------------------------------------------
Time Complexity: O(N)
------------------------------------------------------------
- Each node is visited once.

------------------------------------------------------------
Space Complexity: O(H)
------------------------------------------------------------
- Due to recursive DFS for leaves.
- H is the height of the tree.

------------------------------------------------------------
*/

//////////////////////////////////////////////////////////////////////////////////////
// Approach 2 : Iterative Using Stack & Queue
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    bool isLeaf(TreeNode* node)
    {
        return !node->left && !node->right;
    }

    vector<int> boundaryTraversalIterative(TreeNode* root)
    {
        if (!root) return {};
        vector<int> res;

        // Root (only if not leaf)
        if (!isLeaf(root)) res.push_back(root->val);

        // Left boundary (excluding leaves)
        TreeNode* curr = root->left;
        while (curr)
        {
            if (!isLeaf(curr)) res.push_back(curr->val);
            curr = curr->left ? curr->left : curr->right;
        }

        // Leaves (iterative DFS)
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* node = st.top();
            st.pop();
            if (isLeaf(node))
            {
                res.push_back(node->val);
            }
            else
            {
                // Right pushed first to ensure left is processed first
                if (node->right) st.push(node->right);
                if (node->left) st.push(node->left);
            }
        }

        // Right boundary (excluding leaves, bottom-up)
        curr = root->right;
        vector<int> temp;
        while (curr)
        {
            if (!isLeaf(curr)) temp.push_back(curr->val);
            curr = curr->right ? curr->right : curr->left;
        }
        reverse(temp.begin(), temp.end());
        for (int x : temp) res.push_back(x);

        return res;
    }
};

/////////////////////////////////////////////////////////////////////////
//Approach 3 : Single-Pass BFS-Based Boundary Traversal
class BoundaryBFS
{
public:
    vector<int> singlePassBoundary(TreeNode* root)
    {
        if (!root) return {};
        vector<int> res;
        unordered_set<TreeNode*> added;

        res.push_back(root->val);
        added.insert(root);

        queue<pair<TreeNode*, int>> q; // {node, level}
        q.push({root, 0});

        map<int, TreeNode*> leftmost;
        map<int, TreeNode*> rightmost;
        vector<TreeNode*> leaves;

        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; ++i)
            {
                auto [node, level] = q.front();
                q.pop();

                if (!node) continue;

                if (leftmost.find(level) == leftmost.end())
                    leftmost[level] = node;
                rightmost[level] = node;

                if (!node->left && !node->right)
                    leaves.push_back(node);

                if (node->left) q.push({node->left, level + 1});
                if (node->right) q.push({node->right, level + 1});
            }
        }

        // Add left boundary (skip root)
        for (auto& [lvl, node] : leftmost)
        {
            if (node != root && !added.count(node) && !(!node->left && !node->right))
            {
                res.push_back(node->val);
                added.insert(node);
            }
        }

        // Add all leaves
        for (TreeNode* leaf : leaves)
        {
            if (!added.count(leaf))
            {
                res.push_back(leaf->val);
                added.insert(leaf);
            }
        }

        // Add right boundary in reverse (skip root)
        vector<int> rightTemp;
        for (auto it = rightmost.rbegin(); it != rightmost.rend(); ++it)
        {
            TreeNode* node = it->second;
            if (node != root && !added.count(node) && !(!node->left && !node->right))
            {
                rightTemp.push_back(node->val);
                added.insert(node);
            }
        }
        res.insert(res.end(), rightTemp.begin(), rightTemp.end());

        return res;
    }
};
