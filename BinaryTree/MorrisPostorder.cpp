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
    vector<int> morrisPostorder(TreeNode *root)
    {
        vector<int> result;
        TreeNode dummy(0);
        dummy.left = root;
        TreeNode *curr = &dummy;

        while (curr)
        {
            if (!curr->left)
            {
                curr = curr->right;
            }
            else
            {
                TreeNode *pred = curr->left;
                while (pred->right && pred->right != curr)
                {
                    pred = pred->right;
                }

                if (!pred->right)
                {
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    collectReverse(curr->left, pred, result);
                    pred->right = nullptr;
                    curr = curr->right;
                }
            }
        }

        return result;
    }

    void collectReverse(TreeNode *from, TreeNode *to, vector<int> &res)
    {
        reversePath(from, to);
        TreeNode *node = to;
        while (true)
        {
            res.push_back(node->val);
            if (node == from)
                break;
            node = node->right;
        }
        reversePath(to, from);
    }

    void reversePath(TreeNode *from, TreeNode *to)
    {
        if (from == to)
            return;
        TreeNode *x = from, *y = from->right, *z;
        while (x != to)
        {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
        }
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
    vector<int> postorder = sol.morrisPostorder(root);

    cout << "Morris Postorder: ";
    for (int val : postorder)
        cout << val << " ";
    cout << endl;
}

/*

Approach (Morris Postorder):

- Postorder: Left → Right → Node
- Use a dummy node with left = root.
- Use threading to connect predecessor’s right to current node.
- But unlike inorder/preorder, we process nodes AFTER left and right are done.
- To do this:
   1. When thread is about to be broken, we reverse right edge of subtree (from current->left to pred).
   2. Visit nodes in that reversed path.
   3. Restore tree by reversing again.

Key:
- Use reversePath() to reverse right edge of a path.
- Use collectReverse() to add those values.

Tree:
         4
        / \
       2   5
      / \
     1   3

Reverse visiting path like: 1→2→3 (visit in reverse)
Final Output: [1 3 2 5 4]

Time: O(n), Space: O(1)
*/

