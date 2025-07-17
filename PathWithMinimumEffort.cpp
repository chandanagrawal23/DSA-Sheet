class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& a) 
    {
        int n = a.size();
        int m = a[0].size();

        int left = 0;
        int right = -1;

        // Find the maximum height in the matrix to set right bound for binary search
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                right = max(right, a[i][j]);
            }
        }

        int result = right;

        // Binary search on the minimum "maximum difference" we can tolerate
        while (left <= right) 
        {
            int mid = (left + right) / 2;

            // Check if path exists with effort <= mid
            if (canReach(a, mid)) 
            {
                result = mid;          // mid is a possible answer, try smaller
                right = mid - 1;
            }
            else
            {
                left = mid + 1;        // increase the threshold
            }
        }

        return result;
    }

    // Helper function to check if path exists with max diff ≤ allowedDiff using BFS
    bool canReach(vector<vector<int>>& a, int allowedDiff) 
    {
        // Direction vectors: Left, Right, Up, Down
        int X[4] = {0, 0, -1, 1};
        int Y[4] = {-1, 1, 0, 0};
        int n = a.size();
        int m = a[0].size();

        // Visited array to avoid revisiting cells
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        // Standard BFS
        while (!q.empty()) 
        {
            int oldX = q.front().first;
            int oldY = q.front().second;
            q.pop();

            // If we reach the bottom-right cell
            if (oldX == n - 1 && oldY == m - 1)
                return true;

            for (int i = 0; i < 4; i++) 
            {
                int nx = oldX + X[i];
                int ny = oldY + Y[i];

                // Check bounds and if not visited
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny]) 
                {
                    int diff = abs(a[oldX][oldY] - a[nx][ny]);

                    // Move only if the absolute difference is within allowed limit
                    if (diff <= allowedDiff) 
                    {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }

        // If we exhaust BFS and don't reach (n-1, m-1)
        return false;
    }
};
/*
Approach:
- We use binary search on the answer (the max effort allowed).
- For each mid, we check if we can reach the destination using BFS.
- While doing BFS, we only move to a neighbor cell if the height difference
  between current and next cell is ≤ mid.
- If we can reach the end, we try a smaller mid; else, we increase the mid.
- This helps us find the minimum maximum difference needed along the path.

Time Complexity:
- Binary search: O(log(maxHeight))
- For each mid: BFS → O(N * M)
- So total: O(N * M * log(maxHeight))

Space Complexity:
- O(N * M) for visited matrix and queue.
*/
