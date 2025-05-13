class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        // Directions for 8 possible moves (vertical, horizontal, and diagonal)
        int X[8] = {0, 0, 1, -1, -1, 1, 1, -1};
        int Y[8] = {1, -1, 0, 0, 1, -1, 1, -1};

        int r = grid.size();
        int c = grid[0].size();
        int dist = 0;

        queue<pair<int, int>> q;

        // If starting cell is blocked, return -1
        if (grid[0][0] != 0)
            return -1;

        // Start BFS from (0,0)
        q.push({0, 0});
        grid[0][0] = 1;  // Mark as visited

        while (!q.empty()) {
            int n = q.size();
            while (n--) {
                pair<int, int> pr = q.front(); q.pop();
                int x = pr.first;
                int y = pr.second;

                // If destination is reached, return distance + 1
                if (x == r - 1 && y == c - 1)
                    return dist + 1;

                // Check all 8 directions
                for (int i = 0; i < 8; i++) {
                    int newX = x + X[i];
                    int newY = y + Y[i];

                    // Check boundaries and if cell is unvisited (0)
                    if (newX >= 0 && newX < r && newY >= 0 && newY < c && grid[newX][newY] == 0) {
                        q.push({newX, newY});
                        grid[newX][newY] = 1;  // Mark as visited
                    }
                }
            }

            // Increment distance after exploring one level
            dist++;
        }

        // If no path found
        return -1;
    }
};
