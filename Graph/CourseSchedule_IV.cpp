class Solution 
{
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) 
    {
        vector<vector<bool>> isPrerequisite(numCourses, vector<bool>(numCourses, false)); // isPrerequisite[i][j] = true if i is prereq of j
        vector<vector<int>> adj(numCourses); // adjacency list
        vector<int> indegree(numCourses, 0); // for topological sort

        // Build the graph
        for (auto& pre : prerequisites) 
        {
            int u = pre[0], v = pre[1];
            adj[u].push_back(v);
            isPrerequisite[u][v] = true;
            indegree[v]++;
        }

        // Topological sort using Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < numCourses; i++) 
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty()) 
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) 
            {
                // If i is prerequisite of node → then i is also prerequisite of neighbor
                for (int i = 0; i < numCourses; i++) 
                {
                    if (isPrerequisite[i][node]) 
                    {
                        isPrerequisite[i][neighbor] = true;
                    }
                }

                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        // Answer queries
        vector<bool> res;
        for (auto& query : queries) 
        {
            res.push_back(isPrerequisite[query[0]][query[1]]);
        }

        return res;
    }
};

/*
1. Represent graph using adjacency list.
2. Use a 2D matrix `isPrerequisite[i][j]` to track transitive dependencies.
3. Use Kahn's algorithm (topological sort) to process nodes in dependency order.
4. For each edge u → v:
   - If `x` is a prerequisite of `u`, then `x` is also a prerequisite of `v`
5. Answer each query using pre-computed matrix.

✅ Time Complexity:
- Building graph: O(E)
- Topo sort + propagation: O(N³) in worst case (nested loops)
- Querying: O(Q)

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// we can solve using plain BFS too -

class Solution 
{
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) 
    {
        vector<vector<int>> adj(numCourses);
        for (auto& p : prerequisites) 
        {
            adj[p[0]].push_back(p[1]);
        }

        // result[i][j] = true if i is a prerequisite of j
        vector<vector<bool>> reachable(numCourses, vector<bool>(numCourses, false));

        // For each node, do BFS and mark reachable nodes
        for (int i = 0; i < numCourses; i++) 
        {
            queue<int> q;
            vector<bool> visited(numCourses, false);
            q.push(i);

            while (!q.empty()) 
            {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) 
                {
                    if (!visited[neighbor]) 
                    {
                        visited[neighbor] = true;
                        reachable[i][neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }

        // Answer each query
        vector<bool> ans;
        for (auto& q : queries) 
        {
            ans.push_back(reachable[q[0]][q[1]]);
        }

        return ans;
    }
};
/*
Goal:
Given prerequisites and queries, for each query (u → v), check whether course `u` is a (direct or indirect) prerequisite of `v`.

 Strategy (BFS-based):
1. Represent the course prerequisites as a directed graph.
2. For every course `i`, perform a BFS starting from `i` to find all courses `j` that are reachable from `i`.
   → If `i` can reach `j`, it means `i` is a prerequisite of `j`.
3. Mark all such reachable nodes in a matrix `reachable[i][j] = true`.
4. For each query (u, v), just return `reachable[u][v]`.

Why it works:
- We're essentially finding **transitive closure** in a Directed Acyclic Graph (DAG).
- In DAGs, if `i → ... → j` via any path, then `i` is a valid prerequisite of `j`.
- BFS ensures we visit all such reachable nodes from `i`, marking each.

Time Complexity:
- BFS from each node: O(N * (N + E)) → N BFS calls, each traversing up to E edges
- Querying: O(Q)

Use this approach only when N is reasonably small (up to ~100–200), else topological sort is better for large graphs.

*/
