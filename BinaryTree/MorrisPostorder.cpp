#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left, *right;

    TreeNode(int val)
    {
        this->val = val;
        left = right = nullptr;
    }
};

class Solution
{
public:
    vector<int> morrisPostorder(TreeNode *root)
    {
        vector<int> res;
        TreeNode *curr = root;

        while (curr != nullptr)
        {
            if (curr->right == nullptr)
            {
                res.push_back(curr->val);
                curr = curr->left;
            }
            else
            {
                TreeNode *predecessor = curr->right;
                while (predecessor->left != nullptr && predecessor->left != curr)
                {
                    predecessor = predecessor->left;
                }

                if (predecessor->left == nullptr)
                {
                    res.push_back(curr->val);
                    predecessor->left = curr;
                    curr = curr->right;
                }
                else
                {
                    predecessor->left = nullptr;
                    curr = curr->left;
                }
            }
        }

        reverse(res.begin(), res.end());
        return res;
    }
};
int main()
{
    /*
            10
           /  \
         20    30
              /  \
            40    50
    */

    TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->right = new TreeNode(30);
    root->right->left = new TreeNode(40);
    root->right->right = new TreeNode(50);

    Solution sol;
    vector<int> result = sol.morrisPostorder(root);

    cout << "Morris Postorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Approach: Morris Postorder Traversal (GFG Style)

Postorder traversal: Left → Right → Node

1. We simulate reverse preorder: Root → Right → Left.
2. We traverse the tree by modifying right subtree pointers to make temporary threads.
3. During traversal:
   - If right child is NULL: record the current node, move to left.
   - Else, find the inorder predecessor (leftmost node in right subtree).
     - If predecessor->left == NULL:
        - Create a thread: predecessor->left = current.
        - Save current->val into result.
        - Move to right child.
     - Else:
        - Thread exists: remove it and move to left child.

4. Finally, reverse the result vector to get correct postorder sequence.

Example Tree:
        10
       /  \
     20    30
          /  \
        40    50

Threading and traversal flow:
- Start at 10 → go right to 30 → go right to 50 (add 10, 30, 50 to res)
- Then rewind back via threads, go left to 40 → finally to 20 (add 40, 20)
- res before reverse: [10, 30, 50, 40, 20]
- Final postorder:     [20, 40, 50, 30, 10]

Time Complexity:  O(n)
Space Complexity: O(1) auxiliary (only output vector used)
*/

