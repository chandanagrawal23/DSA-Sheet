class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int rows = maze.size();
        int cols = maze[0].size();
        
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
        distance[start[0]][start[1]] = 0;
        
        vector<vector<int>> directions{{0,1}, {0,-1}, {-1,0}, {1,0}};
        queue<pair<int,int>> q;
        q.push({start[0], start[1]});
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int x = r + dir[0];
                int y = c + dir[1];
                int count = 0;
                
                // roll until hitting a wall or boundary
                while (x >= 0 && y >= 0 && x < rows && y < cols && maze[x][y] == 0) {
                    x += dir[0];
                    y += dir[1];
                    count++;
                }
                
                // step back to the last valid cell
                x -= dir[0];
                y -= dir[1];
                
                if ( distance[x][y] > (distance[r][c] + count) ) {
                    distance[x][y] = distance[r][c] + count;
                    q.push({x, y});
                }
            }
        }
        
        return distance[destination[0]][destination[1]] == INT_MAX ? -1 : distance[destination[0]][destination[1]];
    }
};

/*
Short approach:
- Use BFS with a queue to explore positions.
- From each position, roll ball in each direction until wall.
- Keep updating shortest distance to each cell.
- Return distance to destination if reachable, else -1.
*/
