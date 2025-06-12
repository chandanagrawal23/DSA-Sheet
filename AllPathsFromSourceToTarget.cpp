// using BFS
class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        vector<vector<int>> res;
        if (graph.empty())
            return res;

        int target = graph.size() - 1;
        queue<vector<int>> q;
        q.push({0});  // Start BFS from node 0 with path [0]

        while (!q.empty())
        {
            vector<int> path = q.front();
            q.pop();

            int last = path.back();
            if (last == target)
            {
                res.push_back(path);  // Reached destination, store path
                continue;
            }
            // last = 0 , path = [0]
            // 0 -> 1 , 0 -> 2
            for (int neighbor : graph[last])
            {
                path.push_back(neighbor);  // Extend path new path = [0,1] , [0,2]
                q.push(path);              // Add to queue [[0,1]] , [[0,1],[0,2]]
                path.pop_back();           // Backtrack [0] , [0]
            }
        }

        return res;
    }
};

/*
Approach:
- Use BFS where each node in the queue is a path from source.
- For each path, if last node is target, store it.
- Else, extend path to all neighbors and push into queue.

Time Complexity: O(2^n * n) in worst case — exponential paths, each of length up to n.
Space Complexity: O(2^n * n) for storing all possible paths in queue and result.
*/

//=========================================================================================================================================


// using DFS

class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        vector<vector<int>> res;
        vector<int> path;

        dfs(graph, 0, path, res);

        return res;
    }

    // DFS helper function
    void dfs(vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& res)
    {
        path.push_back(node);  // Add current node to the path

        if (node == graph.size() - 1)
        {
            res.push_back(path);  // Reached destination, save path
        }
        else
        {
            for (int neighbor : graph[node])
            {
                dfs(graph, neighbor, path, res);  // Recurse on neighbor
            }
        }

        path.pop_back();  // Backtrack
    }
};

/*
Approach:
- Start DFS from source node 0.
- Track path as we explore neighbors recursively.
- If we reach destination node, save the current path.
- Backtrack after visiting each neighbor.

Time Complexity: O(2^n * n) in worst case — exponential number of paths.
Space Complexity: O(n) recursion stack depth + result space.
*/




