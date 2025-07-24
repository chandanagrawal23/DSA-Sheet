#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node *left, *right;

    Node(int x)
    {
        val = x;
        left = right = nullptr;
    }
};

class Solution
{
public:
    vector<pair<Node *, int>> traversal;

    void levelOrderMorris(Node *root)
    {
        Node *curr = root;
        int level = 0;

        while (curr != nullptr)
        {
            if (curr->left == nullptr)
            {
                traversal.push_back({curr, level});
                curr = curr->right;
                if (curr != nullptr)
                {
                    level += 1;
                }
                else
                {
                    level -= 1;
                }
            }
            else
            {
                Node *predecessor = curr->left;
                int stepsUp = 0;

                while (predecessor->right != nullptr && predecessor->right != curr)
                {
                    predecessor = predecessor->right;
                    stepsUp++;
                }

                if (predecessor->right == curr)
                {
                    predecessor->right = nullptr;
                    curr = curr->right;
                    level -= (stepsUp + 1);
                }
                else
                {
                    traversal.push_back({curr, level});
                    predecessor->right = curr;
                    curr = curr->left;
                    level += 1;
                }
            }
        }
    }

    vector<vector<int>> getLevelOrder(Node *root)
    {
        traversal.clear();
        levelOrderMorris(root);

        int height = 0;
        for (auto &[node, lvl] : traversal)
        {
            height = max(height, lvl + 1);
        }

        vector<vector<int>> result(height);
        for (auto &[node, lvl] : traversal)
        {
            result[lvl].push_back(node->val);
        }

        return result;
    }
};

int main()
{
    Node *root = new Node(5);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(6);

    Solution sol;
    vector<vector<int>> ans = sol.getLevelOrder(root);

    for (auto &level : ans)
    {
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

/**
Approach: Morris-based Level Order Traversal (Modified from GFG)

- Traditional Morris Traversal is for Inorder traversal using O(1) space by creating temporary threads.
- GFG modifies this idea to track levels during Morris traversal for simulating Level Order.

Key Concepts:
1. During Morris traversal:
   - If a node has no left child:
     - Record (node, level)
     - Move right; increment level
   - If it has a left child:
     - Find inorder predecessor (rightmost of left subtree).
     - If it's not threaded:
         - Create thread to current node
         - Record (node, level)
         - Move left; increment level
     - If it's already threaded:
         - Remove thread
         - Move right; decrement level by steps taken + 1

2. This creates a flat sequence of (node, level) during traversal.

3. After traversal:
   - Scan and group nodes level-wise using recorded level.

Example:

       5
      / \
     2   3
      \
       6

Threading and traversal sequence:
→ Visit 5, left exists → find pred = 6 → thread 6→5 → move to 2 (level+1)
→ Visit 2, left null → record 2, move to 6 (level+1)
→ 6 has no left → record 6, go to 5 (via thread), undo thread (level-1)
→ back to 5 → record 5, go to 3 (level+1)
→ 3 has no left → record 3

Final Sequence: [(2,1), (6,2), (5,0), (3,1)]
→ Level 0: 5
→ Level 1: 2 3
→ Level 2: 6

Time Complexity: O(n)
Space Complexity: O(n) to store level info
*/
