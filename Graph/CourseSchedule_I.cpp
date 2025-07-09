class Solution 
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) 
    {
        vector<vector<int>> graph(numCourses);       // Adjacency list
        vector<int> inDegree(numCourses, 0);         // In-degree of each node

        // Build the graph and compute in-degrees
        for (auto &pre : prerequisites) 
        {
            int course = pre[0];
            int prerequisite = pre[1];

            graph[prerequisite].push_back(course);
            inDegree[course]++;
        }

        queue<int> q;

        // Push all nodes with 0 in-degree into queue
        for (int i = 0; i < numCourses; i++) 
        {
            if (inDegree[i] == 0) 
            {
                q.push(i);
            }
        }

        int coursesTaken = 0;

        // Perform BFS (Kahn's algorithm for topological sort)
        while (!q.empty()) 
        {
            int current = q.front();
            q.pop();
            coursesTaken++;

            for (int neighbor : graph[current]) 
            {
                inDegree[neighbor]--;

                if (inDegree[neighbor] == 0) 
                {
                    q.push(neighbor);
                }
            }
        }

        // If all courses are taken, return true. Otherwise, cycle exists.
        return coursesTaken == numCourses;
    }
};

/*
Approach:
---------
- We model the course prerequisites as a directed graph.
- Each course is a node, and an edge from course A to B means A must be taken before B.
- Use **Kahn's Algorithm** (BFS-based topological sort) to detect if the graph contains a cycle:
    - Compute in-degrees of all nodes.
    - Start with nodes having 0 in-degree (no prerequisites).
    - Repeatedly remove those nodes and update neighbors’ in-degrees.
    - If at the end, we've processed all nodes, there's no cycle — return true.
    - If some nodes remain unprocessed, a cycle exists — return false.

Time Complexity:  O(N + E)
    - N = numCourses, E = number of prerequisites

Space Complexity: O(N + E)
    - Adjacency list and in-degree array
*/
