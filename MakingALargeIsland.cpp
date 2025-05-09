class Solution {
public:
    int m, n;
    vector<int> dirX = {-1, 1, 0, 0};
    vector<int> dirY = {0, 0, -1, 1};
    unordered_map<int, int> componentSize;

    int largestIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int nextColor = 2; // Start coloring from 2
        int maxIsland = 0;

        // First pass: paint each island and calculate their sizes
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    int size = paint(grid, r, c, nextColor);
                    componentSize[nextColor] = size;
                    maxIsland = max(maxIsland, size);
                    ++nextColor;
                }
            }
        }

        // Second pass: try changing each 0 to 1 and compute new island size
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 0) {
                    unordered_set<int> neighbors;
                    int newSize = 1;

                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dirX[i], nc = c + dirY[i];
                        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 1) {
                            neighbors.insert(grid[nr][nc]);
                        }
                    }

                    for (int color : neighbors) {
                        newSize += componentSize[color];
                    }

                    maxIsland = max(maxIsland, newSize);
                }
            }
        }

        return maxIsland == 0 ? m * n : maxIsland;
    }

    int paint(vector<vector<int>>& grid, int r, int c, int color) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != 1) return 0;

        grid[r][c] = color;
        int area = 1;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dirX[i], nc = c + dirY[i];
            area += paint(grid, nr, nc, color);
        }

        return area;
    }
};
