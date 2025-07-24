/*
Approach:

- Water can flow from a cell to its neighbor if the neighbor's height is "less than or equal" to current cell.
  So water always flows "downhill or flat".

- We reverse this logic:
  - Instead of checking from each cell if it can reach an ocean,
  - We "start BFS from ocean border cells", and explore all cells that can reach the ocean by flowing "uphill".

- Why this works:
  - If water can flow from A → B (means B.height <= A.height),
    then in reverse BFS we go from B → A only if A.height >= B.height.
  - So we ensure `heights[nx][ny] >= heights[x][y]` while doing BFS from ocean borders.

- Perform BFS from:
    - Top & left edges (Pacific)
    - Bottom & right edges (Atlantic)

- Mark all cells reachable by each ocean.
- The final result is all coordinates that are reachable from "both" oceans.

Time Complexity: O(m * n)
- Each cell is visited at most twice (once for each ocean BFS)

Space Complexity: O(m * n)
- For visited arrays and queues
*/
class Solution
{
public:
    const vector<pair<int, int>> DIR = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int n, m;

    void bfs(queue<pair<int, int>> &q, vector<vector<int>> &heights, vector<vector<bool>> &visited)
    {
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : DIR)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Only move to neighbor if it's higher or same height and not visited
                if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                    !visited[nx][ny] && heights[nx][ny] >= heights[x][y])
                {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        n = heights.size();
        m = heights[0].size();

        vector<vector<bool>> pacific(n, vector<bool>(m, false));
        vector<vector<bool>> atlantic(n, vector<bool>(m, false));
        queue<pair<int, int>> pacQ, atlQ;

        // Push Pacific border cells (top and left)
        for (int i = 0; i < n; ++i)
        {
            pacific[i][0] = true; // These Cell Touches the pacific ocean left side
            pacQ.push({i, 0});
        }

        for (int j = 0; j < m; ++j)
        {
            pacific[0][j] = true; // These Cell Touches the pacific ocean top side
            pacQ.push({0, j});
        }

        // Push Atlantic border cells (bottom and right)
        for (int i = 0; i < n; ++i)
        {
            atlantic[i][m - 1] = true; // These Cell Touches the Atlantic ocean right side
            atlQ.push({i, m - 1});
        }

        for (int j = 0; j < m; ++j)
        {
            atlantic[n - 1][j] = true; // These Cell Touches the Atlantic ocean bottom side
            atlQ.push({n - 1, j});
        }

        // Run BFS from each ocean
        bfs(pacQ, heights, pacific);
        bfs(atlQ, heights, atlantic);

        // Collect coordinates that can reach both oceans
        vector<vector<int>> result;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (pacific[i][j] && atlantic[i][j])
                {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};
