//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution 
{
public:
    // Direction vectors: right, left, down, up (matching grid values 1, 2, 3, 4)
    vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int minCost(vector<vector<int>>& grid) 
    {
        int numRows = grid.size(), numCols = grid[0].size();

        // Min-heap: {cost, row, col}
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;

        vector<vector<int>> minCost(numRows, vector<int>(numCols, INT_MAX));
        minCost[0][0] = 0;
        pq.push({0, 0, 0}); // {cost, row, col}

        while (!pq.empty()) 
        {
            auto [costSoFar, row, col] = pq.top();
            pq.pop();

            if (costSoFar > minCost[row][col])
            {
                continue;
            }

            for (int dir = 0; dir < 4; dir++) 
            {
                int newRow = row + dirs[dir][0];
                int newCol = col + dirs[dir][1];
                // Add cost=1 if we need to change direction
                int moveCost = (grid[row][col] != (dir + 1)) ? 1 : 0;

                if (isValid(newRow, newCol, numRows, numCols) && ((costSoFar + moveCost) < minCost[newRow][newCol]))
                {
                    minCost[newRow][newCol] = costSoFar + moveCost;
                    pq.push({minCost[newRow][newCol], newRow, newCol});
                }
            }
        }

        return minCost[numRows - 1][numCols - 1];
    }

private:
    bool isValid(int row, int col, int numRows, int numCols) 
    {
        return row >= 0 && row < numRows && col >= 0 && col < numCols;
    }
};

/*
Detailed Approach:

- Grid cells contain directions: 1=→, 2=←, 3=↓, 4=↑.
- Moving in the indicated direction costs 0; any other direction costs 1.

We aim to minimize the cost to reach (n-1, m-1) from (0, 0).

Dijkstra’s Algorithm:
- Treat each cell as a node, and each valid move as an edge with cost 0 or 1.
- Use a min-heap priority queue storing {cost, row, col}.
- At each step, process the node with the lowest cost so far.
- Update neighbors if a cheaper cost path is found.
- Once a node is visited with minimum cost, we don’t need to revisit it.

Time Complexity: O(m * n * log(m * n))  
Space Complexity: O(m * n)
*/
