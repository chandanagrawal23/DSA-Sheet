class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& h : highways) {
            int u = h[0], v = h[1], w = h[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // dist[city][d] = minimum cost to reach 'city' using 'd' discounts
        vector<vector<int>> dist(n, vector<int>(discounts + 1, INT_MAX));
        dist[0][0] = 0;

        // Min heap: {cost, city, discounts_used}
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
        pq.push({0, 0, 0});

        while (!pq.empty()) 
        {
            auto [cost, city, d_used] = pq.top();
            pq.pop();

            // If we reached the destination
            if (city == n - 1)
                return cost;

            if (cost > dist[city][d_used])
                continue; // Already found a better way to this state

            for (auto& [nei, toll] : graph[city]) 
            {
                // Case 1: Go without discount
                if ( (cost + toll) < dist[nei][d_used]) 
                {
                    dist[nei][d_used] = cost + toll;
                    pq.push({dist[nei][d_used], nei, d_used});
                }

                // Case 2: Go with discount (if we have any left)
                if (d_used < discounts) 
                {
                    int discountedToll = toll / 2;
                    if ( (cost + discountedToll) < dist[nei][d_used + 1]) 
                    {
                        dist[nei][d_used + 1] = cost + discountedToll;
                        pq.push({dist[nei][d_used + 1], nei, d_used + 1});
                    }
                }
            }
        }

        // If we never reach city n-1
        return -1;
    }
};
/*
Approach:
---------
- We use a modified Dijkstra’s algorithm to find the shortest cost from city 0 to city n-1,
  where we can use at most 'discounts' number of 50% off coupons on highways.
- State: (current_city, discounts_used) → tracked using a 2D dist array.
- At each step, for every neighbor, we consider two options:
    1. Move without discount.
    2. Move with a discount (if we still have any).
- Use a min-heap (priority_queue with greater<>) to always process the minimum-cost path first.
- If a shorter path to a state is found, update it and push into the heap.

Time Complexity:
----------------
- O(E * (discounts + 1) * log(E * discounts))
  where E = number of edges (highways), and discounts ≤ 500

Space Complexity:
-----------------
- O(n * (discounts + 1)) for the distance table
- O(E) for the graph

*/
