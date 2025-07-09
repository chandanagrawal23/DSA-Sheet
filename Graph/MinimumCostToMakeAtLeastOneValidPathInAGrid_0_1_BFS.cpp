class Solution 
{
public:
    // Direction vectors: right, left, down, up (matching grid values 1, 2, 3, 4)
    vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int minCost(vector<vector<int>>& grid) 
    {
        int numRows = grid.size(), numCols = grid[0].size();

        // Track minimum cost to reach each cell
        vector<vector<int>> minCost(numRows, vector<int>(numCols, INT_MAX));

        // Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
        deque<pair<int, int>> dq;
        dq.push_front({0, 0});
        minCost[0][0] = 0;

        while (!dq.empty()) 
        {
            auto [row, col] = dq.front();
            dq.pop_front();

            // Try all four directions
            for (int dir = 0; dir < 4; dir++) 
            {
                int newRow = row + dirs[dir][0];
                int newCol = col + dirs[dir][1];
                // Add cost=1 if we need to change direction
                int cost = (grid[row][col] != (dir + 1)) ? 1 : 0;

                if (isValid(newRow, newCol, numRows, numCols) && ( (minCost[row][col] + cost) < minCost[newRow][newCol])) 
                {
                    minCost[newRow][newCol] = minCost[row][col] + cost;

                    if (cost == 1) 
                    {
                        dq.push_back({newRow, newCol});
                    } 
                    else 
                    {
                        dq.push_front({newRow, newCol});
                    }
                }
            }
        }

        return minCost[numRows - 1][numCols - 1];
    }

private:
    // Check if coordinates are within grid bounds
    bool isValid(int row, int col, int numRows, int numCols) 
    {
        return row >= 0 && row < numRows && col >= 0 && col < numCols;
    }
};

/*
Detailed Approach:

- Each cell in the grid has a default direction it wants to move:
    1 → right, 2 → left, 3 → down, 4 → up
- Moving in that specified direction costs 0.
- Moving in any other direction costs 1 (like changing the arrow).

We want to find the minimum cost to go from (0,0) to (n-1,m-1).

To solve this efficiently, we use **0-1 BFS**:
- Use a deque instead of a normal queue.
- Push cells with cost 0 to the front of the deque (explored earlier).
- Push cells with cost 1 to the back (explored later).
- This works similarly to Dijkstra’s algorithm but optimized for edges with only 0 and 1 weights.

We track the minimum cost to each cell using a 2D array and only update it when a cheaper path is found.

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/



