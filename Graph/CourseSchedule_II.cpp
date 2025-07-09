class Solution 
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) 
    {
        vector<vector<int>> graph(numCourses);     // Adjacency list
        vector<int> indegree(numCourses, 0);       // In-degree of each node

        // Build the graph and compute indegrees
        for (auto &pre : prerequisites) 
        {
            int course = pre[0];
            int prerequisite = pre[1];
            graph[prerequisite].push_back(course);
            indegree[course]++;
        }

        queue<int> q;
        vector<int> order;

        // Add all nodes with indegree 0 to the queue
        for (int i = 0; i < numCourses; i++) 
        {
            if (indegree[i] == 0) 
            {
                q.push(i);
            }
        }

        // Standard Kahn’s Algorithm
        while (!q.empty()) 
        {
            int current = q.front();
            q.pop();
            order.push_back(current);

            for (int neighbor : graph[current]) 
            {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) 
                {
                    q.push(neighbor);
                }
            }
        }

        // If we couldn’t include all nodes → cycle exists
        if (order.size() != numCourses) 
        {
            return {};
        }

        return order;
    }
};

/*
Approach (BFS / Kahn's Algorithm for Topological Sort):
-------------------------------------------------------
- Build the adjacency list for the graph.
- Track the indegree (number of prerequisites) for each course.
- Initialize a queue with courses having indegree 0 (no prerequisites).
- Repeatedly:
    - Remove a course from the queue
    - Add it to the result order
    - Reduce indegree of all its neighbors
    - If any neighbor’s indegree becomes 0 → add to queue
- If the result contains all courses, return it.
- Else, a cycle exists → return empty array.

Time Complexity:  O(N + E)
    - N = number of courses
    - E = number of prerequisites

Space Complexity: O(N + E)
    - Graph + indegree + queue + result array
*/
