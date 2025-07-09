class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) 
    {
        int m = moveTime.size();
        int n = moveTime[0].size();

        // Min-heap storing: {time to reach, row, col, check flag}
        priority_queue<array<int, 4>, vector<array<int, 4>>, greater<>> heap;

                // or
        // priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>> heap;

        // Start at (0, 0) with time = 0 and initial check = true
        heap.push({0, 0, 0, true});

        // 4-directional movement
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        // Track visited cells to avoid reprocessing
        set<pair<int, int>> visited;

        while (!heap.empty()) 
        {
            auto [time, r, c, check] = heap.top(); // Extract state
            heap.pop();

            // If reached bottom-right cell, return total time
            if (r == m - 1 && c == n - 1) 
                return time;

            // Determine time increment based on current flag
            int delay = check ? 1 : 2;

            // Explore all valid neighboring cells
            for (auto& dir : directions) 
            {
                int newR = r + dir[0];
                int newC = c + dir[1];

                // Check bounds and whether cell is already visited
                if (newR >= 0 && newR < m && newC >= 0 && newC < n && !visited.count({newR, newC}))
                {
                    // Push the new state with updated time and flipped check flag
                    int arrivalTime = max(time, moveTime[newR][newC]) + delay;
                    heap.push({arrivalTime, newR, newC, !check});
                    visited.insert({newR, newC});
                }
            }
        }

        // Destination not reachable
        return -1;
    }
};


/*
Approach:

We are solving a variant of Dijkstra's algorithm where:
- Each move has a time cost that depends on a toggling flag (check).
- If check is true, delay = 1; otherwise, delay = 2.
- You can only enter a cell at time ≥ moveTime[row][col].

For every step:
- We store current time, position, and the `check` flag in a min-heap.
- From each cell, we push all valid neighbors with the new time and toggled check flag.
- We always expand the next minimum time state from the priority queue.

This guarantees that we reach the destination in minimum time, respecting constraints.

Time Complexity:  O(m * n * log(m * n))
  - Each cell is visited at most once.

Space Complexity: O(m * n)
  - For visited set and heap storage.
*/
