class Solution {
public:
    int numIslands(vector<vector<char>>& grid) 
    {
        int n = grid.size();
        int m = grid[0].size();
        int countIsland = 0; // Count of islands

        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                if (grid[i][j] == '1') 
                { // Found an unvisited land
                    dfs(grid, i, j, n, m); // Visit entire island
                    countIsland++; // Increase island count
                }
            }
        }
        return countIsland;
    }

    void dfs(vector<vector<char>>& grid, int i, int j, int n, int m) 
    {
        // Base case: out of bounds or water
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != '1') 
            return;

        grid[i][j] = '0'; // Mark as visited

        // Visit all 4 directions
        dfs(grid, i - 1, j, n, m);
        dfs(grid, i, j - 1, n, m);
        dfs(grid, i + 1, j, n, m);
        dfs(grid, i, j + 1, n, m);
    }
};

/*

// USING  BFS

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int countIslands = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    bfs(grid, i, j, n, m); // Start BFS from current land
                    countIslands++;
                }
            }
        }
        return countIslands;
    }

    void bfs(vector<vector<char>>& grid, int i, int j, int n, int m) {
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '0'; // Mark as visited

        // All 4 directions
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                // If valid and is land
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == '1') {
                    grid[nx][ny] = '0'; // Mark as visited
                    q.push({nx, ny});
                }
            }
        }
    }
};

*/
