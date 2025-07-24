// BFS Based Approach
class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        int maxArea = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    maxArea = max(maxArea, bfs(i, j, grid, m, n));
                }
            }
        }

        return maxArea;
    }

    int bfs(int i, int j, vector<vector<int>> &grid, int m, int n)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = 0; // mark visited
        int area = 1;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : DIR)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < m && ny < n && grid[nx][ny] == 1)
                {
                    grid[nx][ny] = 0;
                    q.push({nx, ny});
                    area++;
                }
            }
        }

        return area;
    }
};

/*
Approach (BFS):
- Traverse each cell in the grid.
- On finding a 1, run BFS from that cell and count connected 1's.
- Mark visited cells by setting them to 0.
- Track the maximum island area found.

Time Complexity: O(m * n)
Space Complexity: O(m * n) — queue space in worst case
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFS Based Approach

class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        int maxArea = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    maxArea = max(maxArea, dfs(i, j, grid, m, n));
                }
            }
        }

        return maxArea;
    }

    int dfs(int i, int j, vector<vector<int>> &grid, int m, int n)
    {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1)
            return 0;

        grid[i][j] = 0; // mark visited

        int area = 1;

        for (auto [dx, dy] : DIR)
        {
            area += dfs(i + dx, j + dy, grid, m, n);
        }

        return area;
    }
};

/*
Approach (DFS):
- Traverse every cell in the grid.
- If the cell is land (1), start a DFS to calculate the area of the island it belongs to.
- Mark cells as visited by setting them to 0.
- Track the maximum area found.

Time Complexity: O(m * n)
Space Complexity: O(m * n) — recursion stack in worst case
*/

