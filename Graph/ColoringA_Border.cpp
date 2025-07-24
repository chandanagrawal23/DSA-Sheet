// DFS Based Solution
class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up

    void dfs(int i,int j,vector<vector<int>> &grid,vector<vector<bool>> &visited,vector<pair<int, int>> &border,int m,int n,int originalColor)
    {
        visited[i][j] = true;
        bool isBorder = false;

        for (auto [dx, dy] : DIR)
        {
            int ni = i + dx;
            int nj = j + dy;

            // If neighbor is out of bounds or of different color → it's a border
            if (ni < 0 || nj < 0 || ni >= m || nj >= n || grid[ni][nj] != originalColor)
            {
                isBorder = true;
            }
            else if (!visited[ni][nj])
            {
                dfs(ni, nj, grid, visited, border, m, n, originalColor);
            }
        }

        if (isBorder)
        {
            border.push_back({i, j}); // push the co-ordinate for border
        }
    }

    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        int m = grid.size();
        int n = grid[0].size();
        int originalColor = grid[row][col];

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> border;

        dfs(row, col, grid, visited, border, m, n, originalColor); // find all border cell in that componnent

        // Paint the border cells
        for (auto &[x, y] : border)
        {
            grid[x][y] = color;
        }

        return grid;
    }
};

/*
Approach:

- Goal: Recolor the "border" of a connected component starting from (row, col).
- A cell belongs to the component if it's reachable using only same-color adjacent cells.
- A "border" cell is one that either:
   1. Lies on the edge of the grid, or
   2. Has a neighbor cell with a different color.

Steps:
1. Use DFS to explore all cells of the component.
2. While visiting, check each cell's 4 directions:
   - If any direction is either out-of-bound or different color, current cell is on border.
3. Push all such border cells into a `border` list.
4. After DFS finishes, change color of only those border cells.

Time Complexity: O(m * n)
- Each cell is visited at most once.

Space Complexity: O(m * n)
- Used for `visited` matrix and `border` list.

💡 Example:
grid = {
    {1, 1, 1, 2},
    {1, 1, 1, 2}, 
    {1, 0, 1, 2},
    {1, 1, 1, 2}
}
row = 0, col = 0, color = 9

- Connected component of 1's includes almost entire left 3x3 grid.
- Border cells are those on the outer edge or touching 0 or 2.
- Only those borders are changed to 9.

Result:
{
    {9, 9, 9, 2},
    {9, 1, 9, 2},
    {9, 0, 9, 2},
    {9, 9, 9, 2}
}

*/

////////////////////////////////////////////////////////////////////////////////////////////
// BFS Based Solution

class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 4 directions

    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        int m = grid.size(), n = grid[0].size();
        int originalColor = grid[row][col];

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> border;

        queue<pair<int, int>> q;
        q.push({row, col});
        visited[row][col] = true;

        while (!q.empty())
        {
            auto [i, j] = q.front();
            q.pop();
            bool isBorder = false;

            for (auto [dx, dy] : DIR)
            {
                int ni = i + dx;
                int nj = j + dy;

                // If adjacent is out of bounds or different color → this is a border cell
                if (ni < 0 || nj < 0 || ni >= m || nj >= n || grid[ni][nj] != originalColor)
                {
                    isBorder = true;
                }
                else if (!visited[ni][nj])
                {
                    visited[ni][nj] = true;
                    q.push({ni, nj});
                }
            }

            if (isBorder)
            {
                border.push_back({i, j});
            }
        }

        // Color only the border cells
        for (auto &[x, y] : border)
        {
            grid[x][y] = color;
        }

        return grid;
    }
};

