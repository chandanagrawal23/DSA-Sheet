class Solution
{
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges)
    {
        vector<int> inDegree(n, 0);   // Stores incoming edge count for each node
        vector<int> result;           // Stores the answer nodes

        // Count in-degrees
        for (const auto& edge : edges)
        {
            int to = edge[1];
            inDegree[to]++;
        }

        // Any node with in-degree 0 must be included in the result
        for (int i = 0; i < n; ++i)
        {
            if (inDegree[i] == 0)
            {
                result.push_back(i);
            }
        }

        return result;
    }
};

/*
Approach:
- A node that has no incoming edges cannot be reached by any other node.
- We must include all such nodes in our result to reach all others.
- Any node with incoming edges can be reached indirectly, so we skip it.

Time Complexity:  O(E + N) — Traverse all edges and nodes once.
Space Complexity: O(N)     — To store in-degree array and result.
*/
