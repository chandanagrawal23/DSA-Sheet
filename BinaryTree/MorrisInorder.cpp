#include<bits/stdc++.h>
using namespace std;


class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = right = nullptr;
    }
};

class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode *curr = root;

        while (curr != nullptr)
        {
            // If no left child, visit current and move right
            if (curr->left == nullptr)
            {
                result.push_back(curr->val);
                curr = curr->right;
            }
            else
            {
                // Find the inorder predecessor (rightmost in left subtree)
                TreeNode *pred = curr->left;

                while (pred->right != nullptr && pred->right != curr)
                {
                    pred = pred->right;
                }

                // First time visiting: create thread and go left
                if (pred->right == nullptr)
                {
                    pred->right = curr;
                    curr = curr->left;
                }
                // Second time: thread exists → break it and visit current
                else
                {
                    pred->right = nullptr;
                    result.push_back(curr->val);
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
        Constructing the tree:
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
    vector<int> inorder = sol.inorderTraversal(root);

    cout << "Inorder Traversal: ";
    for (int val : inorder)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
Approach: Morris Inorder Traversal (No stack, no recursion)

 Goal:
Traverse the binary tree in **inorder** (Left → Root → Right) without using extra space.

 Core Idea:
We temporarily modify the tree to simulate recursion using a "threaded binary tree" technique.
We establish temporary right pointers ("threads") to backtrack from a node's left subtree back to the node itself.

 Steps:
1. Initialize curr = root.
2. While curr is not NULL:
   a. If curr has NO left child:
      → Add curr->val to result.
      → Move to curr->right.

   b. If curr has a left child:
      → Find the **inorder predecessor** of curr (i.e., rightmost node in curr->left subtree).
      → If pred->right is NULL:
         - Set pred->right = curr  ⬅️ (Create a thread)
         - Move curr to curr->left.
      → Else if pred->right == curr:
         - We've returned via thread, so:
           - Break the thread (pred->right = NULL).
           - Add curr->val to result.
           - Move curr to curr->right.

 Inorder Predecessor = the previous node before current in inorder traversal.

 Why this works:
- We're simulating the recursion call stack using threads.
- Every node is visited at most twice — once on the way down (to make a thread), and once on the way up (to process and break the thread).

 Example: Tree
          4
         / \
        2   5
       / \
      1   3

 Expected Inorder: [1, 2, 3, 4, 5]

 Threading Steps:
→ At Node 4:
   - Has left child → go to its inorder predecessor.
   - Left child is 2 → rightmost of 2 is 3.
   - 3 is pred → 3->right = 4 (make a thread from 3 to 4)

         4
        / \
       2   5
      / \
     1   3
          \
           ↘
            4  (← Threaded back)

→ Move curr = 2
→ 2 has left → pred = 1
→ 1->right = 2 (thread)

→ Move curr = 1 → no left
   - Print 1 → [1]
→ Move to 2 (via thread)
   - Break thread → Print 2 → [1, 2]
→ Move to 3 → no left → Print 3 → [1, 2, 3]
→ Move to 4 (via thread)
   - Break thread → Print 4 → [1, 2, 3, 4]
→ Move to 5 → Print 5 → [1, 2, 3, 4, 5]

 Time Complexity: O(n)
- Each node is visited at most twice.

 Space Complexity: O(1)
- No recursion or stack used, only a few pointers.
*/
