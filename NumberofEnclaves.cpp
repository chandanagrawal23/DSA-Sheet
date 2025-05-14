/*

 DFS for each non visited Boundary 1, and after that count remaining 1. 

*/

class Solution 
{
public:
    // Perform DFS to sink all connected land (1s) from a given cell
    int dfs(int row, int col, vector<vector<int>>& grid) 
    {
        // If out of bounds or water, return 0
        if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size() || grid[row][col] == 0)
            return 0;

        // Mark current land as visited
        grid[row][col] = 0;

        // Explore in all 4 directions and count connected land
        return 1 + dfs(row - 1, col, grid) 
                 + dfs(row + 1, col, grid) 
                 + dfs(row, col - 1, grid) 
                 + dfs(row, col + 1, grid);
    }

    int numEnclaves(vector<vector<int>>& grid) 
    {
        int totalLand = 0;

        // Count all land cells (1s)
        for (int row = 0; row < grid.size(); row++) 
        {
            for (int col = 0; col < grid[0].size(); col++) 
            {
                totalLand += grid[row][col];
            }
        }

        int boundaryLand = 0;

        // Sink all land cells connected to boundaries
        for (int row = 0; row < grid.size(); row++) 
        {
            for (int col = 0; col < grid[0].size(); col++) 
            {
              // Check if the cell is on the boundary
              bool isBoundary = (row == 0 || col == 0 || row == grid.size() - 1 || col == grid[0].size() - 1);
              // If it's a land cell and on boundary , then perform DFS to sink the connected land
              if (isBoundary and grid[row][col] == 1) 
              {
                  boundaryLand += dfs(row, col, grid);
              }
            }
        }

        // Enclosed land = total land - boundary-connected land
        return totalLand - boundaryLand;
    }
};

/*

Multi-Source BFS

Push all Boundary '1' into queue and do BFS, which is faster than above DFS for each non visited Boundary 1 

*/

class Solution 
{
public:
    int numEnclaves(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        queue<pair<int, int>> q;

        // Add all boundary land cells to the queue and mark them as visited (0)
        for (int row = 0; row < rows; ++row) 
        {
            for (int col = 0; col < cols; ++col) 
            {
                bool isBoundary = (row == 0 || col == 0 || row == rows - 1 || col == cols - 1);
                if (isBoundary && grid[row][col] == 1) 
                {
                    q.push({row, col});
                    grid[row][col] = 0; // Mark as visited
                }
            }
        }

        // Directions: up, down, left, right
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        // BFS to remove all land connected to boundary
        while (!q.empty()) 
        {
            auto [row, col] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) 
            {
                int newRow = row + dr;
                int newCol = col + dc;

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 1) 
                {
                    q.push({newRow, newCol});
                    grid[newRow][newCol] = 0; // Mark as visited
                }
            }
        }

        // Count remaining land cells (enclaves)
        int enclaveCount = 0;
        for (int row = 0; row < rows; ++row) 
        {
            for (int col = 0; col < cols; ++col) 
            {
                if (grid[row][col] == 1) 
                {
                    enclaveCount++;
                }
            }
        }

        return enclaveCount;
    }
};



