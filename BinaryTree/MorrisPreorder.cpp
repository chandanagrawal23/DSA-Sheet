#include <iostream>
#include <vector>
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
    vector<int> morrisPreorder(TreeNode *root)
    {
        vector<int> result;
        TreeNode *curr = root;

        while (curr)
        {
            if (curr->left == nullptr)
            {
                result.push_back(curr->val);
                curr = curr->right;
            }
            else
            {
                TreeNode *pred = curr->left;
                while (pred->right && pred->right != curr)
                {
                    pred = pred->right;
                }

                if (pred->right == nullptr)
                {
                    result.push_back(curr->val); // visit before going left
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    pred->right = nullptr;
                    curr = curr->right;
                }
            }
        }

        return result;
    }
};

int main()
{
    /*
            4
           / \
          2   5
         / \
        1   3
    */
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    vector<int> preorder = sol.morrisPreorder(root);

    cout << "Morris Preorder: ";
    for (int val : preorder)
        cout << val << " ";
    cout << endl;
}

/*

Approach (Morris Preorder):

- Preorder traversal order is: Node → Left → Right.
- The idea is to avoid recursion or stack and traverse using threaded binary tree logic.

Steps:
1. Start from root. While current node is not null:
   - If current->left is null:
       - Visit current (add to result).
       - Go right.
   - Else:
       - Find the inorder predecessor (rightmost node in left subtree).
       - If pred->right is null:
           - Set pred->right = current (thread it).
           - Visit current (before moving left).
           - Move to left child.
       - Else:
           - pred->right == current (thread exists):
               - Remove thread (set to null).
               - Move to right child.

Tree:
         4
        / \
       2   5
      / \
     1   3

Threading:
- 4 has left → pred = 3 → thread 3.right = 4
- go to 2 → pred = 1 → thread 1.right = 2
- go to 1 → no left → print 1 → backtrack to 2
- thread exists → remove → print 2 → go to 3
- print 3 → go to 4
- thread exists → remove → print 4 → go to 5 → print 5

Output: [1, 2, 3, 4, 5]

Time: O(n), Space: O(1)
*/

