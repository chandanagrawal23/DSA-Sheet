class Solution
{
public:
    int swimInWater(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int low = grid[0][0], high = n * n - 1;
        int result = high;

        // Binary search on minimum time (water level)
        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (canReach(grid, mid))
            {
                result = mid;
                high = mid - 1; // Try smaller water levels
            }
            else
            {
                low = mid + 1;  // Try larger water levels
            }
        }

        return result;
    }

private:
    // BFS to check if (0,0) to (n-1,n-1) is reachable with at most water height of any cell <= waterLevel
    bool canReach(vector<vector<int>> &grid, int waterLevel)
    {
        int n = grid.size();
        if (grid[0][0] > waterLevel)
            return false;

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;

        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == n - 1 && y == n - 1)
                return true;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (
                    nx >= 0 && ny >= 0 && nx < n && ny < n &&
                    !visited[nx][ny] && grid[nx][ny] <= waterLevel
                )
                {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        return false;
    }
};

/**
Approach:
- Use binary search to find the minimum water level `t` such that you can travel from (0,0) to (n-1,n-1)
- At each mid level, perform BFS from (0,0) and only move to neighbor (x,y) if `grid[x][y] <= mid`
- If destination is reachable, try smaller `t`. Otherwise, increase `t`.

Time Complexity: O(log(maxHeight) * n²)  
Space Complexity: O(n²)  
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// we can solve like Dijkistra's algorithm too.........

class Solution
{
public:
    int swimInWater(vector<vector<int>>& grid)
    {
        int n = grid.size();
        int maxHeight = max(grid[0][0], grid[n - 1][n - 1]);

        // Min-heap priority queue: {elevation, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;

        while (!pq.empty())
        {
            auto current = pq.top();
            pq.pop();

            int elevation = current[0];
            int x = current[1];
            int y = current[2];

            maxHeight = max(maxHeight, elevation);

            // Reached bottom-right cell
            if (x == n - 1 && y == n - 1)
                return maxHeight;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && !visited[nx][ny])
                {
                    pq.push({grid[nx][ny], nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }

        return 0;
    }
};

/**
Approach (Dijkstra-like):
- Use a min-heap to always choose the next cell with the lowest height.
- From (0,0), we "swim" to neighbors only if they haven't been visited.
- We keep track of the maximum elevation encountered on the path.
- The first time we reach (n-1,n-1), we are guaranteed to have taken the path with the smallest possible max height.

Time Complexity: O(n² * log n) — each cell may be pushed once in the priority queue  
Space Complexity: O(n²) — for visited matrix and the priority queue
*/

