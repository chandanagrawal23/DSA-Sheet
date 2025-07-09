class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) 
    {
        int m = moveTime.size();
        int n = moveTime[0].size();

        // Min-heap: each element is {time to reach, row, col}
        // Using array<3> instead of tuple/vector for speed

        // priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> heap;
                                    // OR
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> heap;

        // Start from top-left cell at time = 0
        heap.push({0, 0, 0});

        // Directions: right, down, left, up
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        // Keep track of visited cells to avoid cycles
        set<pair<int, int>> visited;

        while (!heap.empty()) 
        {
            // Get the state with the least time
            auto [time, r, c] = heap.top();
            heap.pop();

            // If we've reached the bottom-right cell, return the time
            if (r == m - 1 && c == n - 1) 
                return time;

            // Try moving in all 4 directions
            for (auto& dir : directions) 
            {
                int row = r + dir[0];
                int col = c + dir[1];

                // Check if within bounds and not yet visited
                if (row >= 0 && row < m && col >= 0 && col < n && !visited.count({row, col}))
                {
                    // Calculate new time considering cell availability and +1 for move
                    int nextTime = max(time, moveTime[row][col]) + 1;

                    // Push the next state into heap
                    heap.push({nextTime, row, col});

                    // Mark as visited
                    visited.insert({row, col});
                }
            }
        }

        // If unreachable
        return -1;
    }
};

/*
Approach:

We use Dijkstra's algorithm because:
- Each move has a dynamic cost: you can only enter a cell at or after moveTime[row][col], then +1 for the move.
- Among all reachable positions, we always prioritize the one that can be reached the earliest (min-heap based on time).

For each cell, we calculate:
- `nextTime = max(current_time, moveTime[row][col]) + 1`

We continue expanding the smallest-time cell until we reach the bottom-right.

Time Complexity:  O(m * n * log(m * n))
- Each cell is pushed into the heap at most once.

Space Complexity: O(m * n)
- For visited tracking and heap storage.
*/
