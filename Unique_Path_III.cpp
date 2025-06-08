// I extend this problem to print path's too from source to destination, have fun
class Solution
{
public:
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        int startRow = -1;
        int startCol = -1;
        int totalFreeCells = 0;

        // Step 1: Locate start position and count total non-obstacle cells
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] != -1)
                {
                    totalFreeCells++;
                }

                if (grid[i][j] == 1)
                {
                    startRow = i;
                    startCol = j;
                }
            }
        }

        int totalPaths = 0;
        dfs(grid, startRow, startCol, totalFreeCells, totalPaths);

        return totalPaths;
    }

private:
    void dfs(vector<vector<int>> &grid,
             int r,
             int c,
             int remaining,
             int &totalPaths)
    {
        // out of bounds or obstacle
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == -1)
        {
            return;
        }

        // reached ending cell
        if (grid[r][c] == 2)
        {
            if (remaining == 1)
            {
                totalPaths++;
            }
            return;
        }

        // save original cell and mark visited
        int temp = grid[r][c];
        grid[r][c] = -1;

        // explore all 4 directions
        dfs(grid, r + 1, c, remaining - 1, totalPaths);
        dfs(grid, r - 1, c, remaining - 1, totalPaths);
        dfs(grid, r, c + 1, remaining - 1, totalPaths);
        dfs(grid, r, c - 1, remaining - 1, totalPaths);

        // backtrack
        grid[r][c] = temp;
    }
};

/*
-------------------  Short approach  -------------------
1. Count total non-obstacle cells (including start & end).
2. Start DFS from '1', mark visited cells with -1.
3. Recurse in 4 directions, reduce `remaining` count.
4. If we reach cell '2' and `remaining == 1` (only end is left), count it as a valid path.
5. Backtrack after each DFS call.


Time Complexity: O(3^N), where N is the number of non-obstacle cells in the grid.

- At the first step, the robot can move in up to 4 directions.
- However, after the first move, it cannot move back to the cell it came from (because it's marked visited),
  so it has at most 3 directions to explore at each subsequent step.
- Hence, the total complexity is roughly O(4 * 3^(N-1)) = O(3^N).

Space Complexity: O(N)
- Due to the recursion stack and the path tracking, which can go as deep as the total number of free cells.
- N is the number of cells that must be visited exactly once (non-obstacle).
*/
