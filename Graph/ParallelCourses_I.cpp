class Solution 
{
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) 
    {
        vector<vector<int>> adj(N + 1);
        vector<int> indegree(N + 1, 0);

        // Build graph
        for (auto& rel : relations) 
        {
            int u = rel[0];
            int v = rel[1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;

        // Push courses with no prerequisites
        for (int i = 1; i <= N; i++) 
        {
            if (indegree[i] == 0) 
                q.push(i);
        }

        int semesters = 0;
        int coursesTaken = 0;

        while (!q.empty()) 
        {
            int size = q.size();
            semesters++;

            // Process all courses available this semester
            for (int i = 0; i < size; i++) 
            {
                int course = q.front(); q.pop();
                coursesTaken++;

                for (int neighbor : adj[course]) 
                {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0)
                        q.push(neighbor);
                }
            }
        }

        // If we have taken all N courses, return number of semesters
        return (coursesTaken == N) ? semesters : -1;
    }
};

/*
Approach:
---------
- We use Kahn’s algorithm (BFS Topological Sort) to process courses semester-wise.
- Every level in BFS represents one semester.
- In each semester, we can take all courses with indegree 0.
- We reduce indegree of neighbors after completing a course.

Cycle Detection:
----------------
- If we cannot take all N courses (coursesTaken != N), a cycle exists and return -1.

Time Complexity: O(N + E)
- N: number of courses
- E: number of prerequisites (edges)

Space Complexity: O(N + E)
- For adjacency list and indegree array.
*/
