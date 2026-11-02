
class Solution
{
public:
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // Step 1: Multi-Source BFS.
    vector<vector<int>> getDistances(vector<vector<int>>& grid)
    {
        int n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<array<int, 2>> q;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k], nc = c + dc[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                    continue;

                if (dist[nr][nc] != -1)
                    continue;

                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }

        return dist;
    }

    // Step 2: BFS feasibility check.
    bool canReach(vector<vector<int>>& dist, int threshold)
    {
        int n = dist.size();

        if (dist[0][0] < threshold)
            return false;

        queue<array<int, 2>> q;
        vector<vector<bool>> vis(n, vector<bool>(n, false));

        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            if (r == n - 1 && c == n - 1)
                return true;

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k], nc = c + dc[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                    continue;

                if (vis[nr][nc] || dist[nr][nc] < threshold)
                    continue;

                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }

        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid)
    {
        int n = grid.size();

        vector<vector<int>> dist = getDistances(grid);

        // Step 3: Binary Search on Answer.
        int low = 0, high = 2 * (n - 1), ans = 0;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (canReach(dist, mid))
            {
                ans = mid;
                low = mid + 1;
            }
            else
                high = mid - 1;
        }

        return ans;
    }
};

/*
Approach: Multi-Source BFS + Binary Search on Answer + BFS

1. Multi-Source BFS:
   Calculate minimum distance of every cell from the nearest thief.

2. Binary Search on Answer:
   Find maximum possible safeness factor.

3. BFS Feasibility Check:
   Traverse only cells with distance >= threshold.
   If destination is reachable, threshold is feasible.

Time Complexity:
   getDistances: O(n^2)
   canReach: O(n^2)
   Binary Search: O(log n)

   Total: O(n^2 * log n)

Space Complexity: O(n^2)
*/
