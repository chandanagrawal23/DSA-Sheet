class Solution 
{
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        // Adjacency list: graph[node] = {neighbor, time}
        vector<vector<pair<int, int>>> adjList(n + 1);
        for (const auto& edge : times) 
        {
            int from = edge[0], to = edge[1], time = edge[2];
            adjList[from].emplace_back(to, time);
        }

        // Min-heap: {time to reach, node}, using array<int, 2>
        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;
        pq.push({0, k});  // Starting at node k with time 0

        vector<int> minTime(n + 1, INT_MAX);  // Min time to reach each node
        minTime[k] = 0;

        while (!pq.empty()) 
        {
            auto [currTime, node] = pq.top();
            pq.pop();

            if (currTime > minTime[node])
                continue;  // Already found a better path

            for (const auto& [neighbor, travelTime] : adjList[node]) 
            {
                int newTime = currTime + travelTime;

                if (newTime < minTime[neighbor]) 
                {
                    minTime[neighbor] = newTime;
                    pq.push({newTime, neighbor});
                }
            }
        }

        int result = 0;
        for (int i = 1; i <= n; ++i) 
        {
            if (minTime[i] == INT_MAX)
                return -1;  // Unreachable node
            result = max(result, minTime[i]);
        }

        return result;
    }
};

/*
 Approach: Dijkstra Algorithm

- Build an adjacency list of the directed graph.
- Use a min-heap (priority_queue with array<int, 2>) to always process
  the next node with the smallest current signal arrival time.
- Update each neighbor’s min arrival time if a shorter path is found.
- Finally, return the maximum arrival time among all nodes.
  If any node is unreachable (i.e., time is still INT_MAX), return -1.

 Time Complexity: O(E log V)
 Space Complexity: O(V + E)
*/
