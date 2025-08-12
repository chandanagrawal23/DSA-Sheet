class Solution
{
public:
    int minTime(int n, vector<vector<int>>& edges)
    {
        if (n == 1)
        {
            return 0;
        }

        // graph[node] = list of {neighbor, startTime, endTime}
        vector<vector<vector<int>>> graph(n);

        for (auto& edge : edges)
        {
            // edge format: [u, v, startTime, endTime]
            graph[edge[0]].push_back({edge[1], edge[2], edge[3]});
        }

        vector<int> time(n, INT_MAX);
        // min heap {currentTime, node}
        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;

        pq.push({0, 0});  

        while (!pq.empty())
        {
            auto [currTime, node] = pq.top();
            pq.pop();

            if (currTime >= time[node])
                continue;

            time[node] = currTime;

            for (auto& edge : graph[node])
            {
                int nxt = edge[0];
                int startTime = edge[1];
                int endTime = edge[2];

                int tempTime = currTime;

                if (tempTime > endTime)
                    continue;  // can't use this edge

                if (tempTime < startTime)
                    tempTime = startTime;  // wait till edge available

                tempTime += 1;  // travel time

                if (tempTime < time[nxt])
                {
                    pq.push({tempTime, nxt});
                }
            }
        }

        return time[n - 1] == INT_MAX ? -1 : time[n - 1];
    }
};

/*
  Approach:
  We model the problem as a shortest path in a graph with time constraints on edges.
  We build an adjacency list where each edge carries a start and end time window.
  Using a modified Dijkstra's algorithm:
  - We keep a min-heap (priority queue) with pairs {current_time, node}.
  - For each extracted node with current_time, we relax its neighbors only if
    the edge is available at that time (current_time within [startTime, endTime]).
  - If current_time is less than startTime, we wait till startTime.
  - Traveling takes 1 unit of time.
  - We keep track of minimum arrival times to nodes in a 'time' array.
  - If a better time to a neighbor is found, we push it to the priority queue.
  - Finally, we return the minimum time to reach node n-1 or -1 if unreachable.
 
  Time Complexity:
  - Let E = number of edges, N = number of nodes.
  - Each edge can be relaxed multiple times, but total relaxations bounded by O(E log N).
  - Each insertion/removal in priority queue costs O(log N).
  - Overall complexity: O(E log N)
 
  Space Complexity:
  - Adjacency list uses O(E) space.
  - Time array uses O(N).
  - Priority queue can hold up to O(N) elements.
  - Total space: O(N + E)
*/
