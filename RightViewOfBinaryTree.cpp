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

    TreeNode(int x)
    {
        val = x;
        left = right = nullptr;
    }

    TreeNode(int x, TreeNode* l, TreeNode* r)
    {
        val = x;
        left = l;
        right = r;
    }
};

// -------------------------------
// Solution Class with All 3 Right View Approaches
// -------------------------------
class Solution
{
public:

    // -----------------------------------------------------
    // 1. RIGHT VIEW USING BFS
    // Level-order traversal, pick last node at each level
    // -----------------------------------------------------
    vector<int> rightViewBFS(TreeNode* root)
    {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode* node = q.front();
                q.pop();

                if (i == size - 1) // last node at this level
                    result.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return result;
    }

    // -----------------------------------------------------
    // 2. RIGHT VIEW USING DFS (Recursive)
    // Right-first DFS; store first node at each level
    // -----------------------------------------------------
    void dfs(TreeNode* node, int level, vector<int>& res)
    {
        if (!node) return;

        if (level == res.size()) // first node at this level
            res.push_back(node->val);

        dfs(node->right, level + 1, res); // right first
        dfs(node->left, level + 1, res);
    }

    vector<int> rightViewDFSRecursive(TreeNode* root)
    {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }

    // -----------------------------------------------------
    // 3. RIGHT VIEW USING DFS (Iterative)
    // Use stack (right-first); record first node per level
    // -----------------------------------------------------
    vector<int> rightViewDFSIterative(TreeNode* root)
    {
        if (!root) return {};

        stack<pair<TreeNode*, int>> st;         // node + level
        unordered_map<int, int> levelMap;       // level -> value
        st.push({root, 0});

        while (!st.empty())
        {
            auto [node, level] = st.top();
            st.pop();

            if (levelMap.find(level) == levelMap.end())
                levelMap[level] = node->val;

            if (node->left) st.push({node->left, level + 1});
            if (node->right) st.push({node->right, level + 1});
        }

        vector<int> res;
        for (int i = 0; i < levelMap.size(); ++i)
            res.push_back(levelMap[i]);

        return res;
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
             /   / \
            4   5   6
               /
              7

        Right view: 1 3 6 7
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->left->left = new TreeNode(7);

    Solution sol;

    vector<int> bfsView = sol.rightViewBFS(root);
    vector<int> dfsRecView = sol.rightViewDFSRecursive(root);
    vector<int> dfsIterView = sol.rightViewDFSIterative(root);

    cout << "Right View (BFS): ";
    for (int x : bfsView) cout << x << " ";
    cout << endl;

    cout << "Right View (DFS Recursive): ";
    for (int x : dfsRecView) cout << x << " ";
    cout << endl;

    cout << "Right View (DFS Iterative): ";
    for (int x : dfsIterView) cout << x << " ";
    cout << endl;

    return 0;
}
