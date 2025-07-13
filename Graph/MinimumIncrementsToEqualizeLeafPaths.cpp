class Solution
{
public:
    int operations = 0;

    // DFS to calculate subtree path sums and count required increases
    long long dfs(int node, int parent, vector<vector<int>>& tree, vector<int>& cost)
    {
        vector<long long> childSums;

        for (int neighbor : tree[node])
        {
            if (neighbor != parent)
            {
                // Get path sum from each child
                childSums.push_back(dfs(neighbor, node, tree, cost));
            }
        }

        // If node has no children, return its cost
        if (childSums.empty())
        {
            return cost[node];
        }

        // Find the max path sum among all children
        long long maxSum = *max_element(childSums.begin(), childSums.end());

        // For all other child paths that are not max, we need to increment
        for (long long sum : childSums)
        {
            if (sum != maxSum)
                operations++;
        }

        // Return max child's path + current node's cost
        return maxSum + cost[node];
    }

    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost)
    {
        vector<vector<int>> tree(n);

        // Build undirected tree
        for (auto& edge : edges)
        {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1, tree, cost);
        return operations;
    }
};

/*

Intuition:
-------------
We want all root-to-leaf path sums to be equal by **only increasing** node costs.

Approach: ( basically a post order traversal)
-------------
- Start DFS from node 0 (the root).
- At each node:
  1. Collect all path sums from its child subtrees.
  2. Find the MAXIMUM among those child path sums.
  3. For any child whose path sum is less than the max, we count one operation to make it equal.
  4. Return `maxChildSum + cost[node]` to the parent.
--------------------------------------------------

Input:
---------
n = 7  
edges = {{0,1}, {0,2}, {1,3}, {1,4}, {2,5}, {2,6}}  
cost = [5, 3, 2, 1, 4, 1, 1]

 Tree structure with cost:
----------------------------
             0(5)
           /     \
       1(3)       2(2)
      /   \      /   \
   3(1)  4(4)  5(1)  6(1)

--------------------------------------------------

 DFS Dry Run:
---------------

Node 3 → leaf → return 1  
Node 4 → leaf → return 4

→ Node 1:
  - children = [3 → 1, 4 → 4]
  - max = 4
  - child 3 is less ⇒ ops++ 
  - return 4 + 3 = 7

Node 5 → leaf → return 1  
Node 6 → leaf → return 1

→ Node 2:
  - children = [5 → 1, 6 → 1]
  - max = 1
  - all equal ⇒ no ops
  - return 1 + 2 = 3

→ Node 0:
  - children = [1 → 7, 2 → 3]
  - max = 7
  - child 2 is less ⇒ ops++ 
  - return 7 + 5 = 12


 Final Answer = 2 operations

 Time Complexity:  O(n)
  Space Complexity: O(n)

*/
