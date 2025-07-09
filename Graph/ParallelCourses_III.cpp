class Solution
{
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time)
    {
        // Build adjacency list and indegree array
        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        vector<int> finishTime(n + 1, 0);

        for (const auto& rel : relations)
        {
            int prereq = rel[0], course = rel[1];
            graph[prereq].push_back(course);
            indegree[course]++;
        }

        queue<int> q;

        // Initialize courses with no prerequisites
        for (int i = 1; i <= n; ++i)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
                finishTime[i] = time[i - 1];
            }
        }

        // Topological sort + longest path DP on DAG
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int next : graph[curr])
            {
                finishTime[next] = max(finishTime[next], finishTime[curr] + time[next - 1]);
                indegree[next]--;
                if (indegree[next] == 0)
                {
                    q.push(next);
                }
            }
        }

        return *max_element(finishTime.begin(), finishTime.end());
    }
};

/*
Approach:
- Build a graph of course dependencies using adjacency list.
- Perform topological sort using BFS.
- Use DP to track the earliest time each course can be finished.
- For each course, update its finish time based on the maximum of its prerequisites' finish times.

Time Complexity: O(N + E)
- N = number of courses, E = number of relations

Space Complexity: O(N + E)
- For graph, indegree, and DP arrays
*/
