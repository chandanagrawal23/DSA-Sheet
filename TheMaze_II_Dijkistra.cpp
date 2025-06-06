#include <vector>
#include <queue>
#include <climits>
#include <array>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int rows = maze.size();
        int cols = maze[0].size();

        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        dist[start[0]][start[1]] = 0;

        // Min-heap: stores {distance, row, col}
        priority_queue< array<int, 3>, vector<array<int, 3>>, greater<> > pq;
        pq.push({0, start[0], start[1]});

        // Directions: right, left, up, down
        vector<int> dr = {0, 0, -1, 1};
        vector<int> dc = {1, -1, 0, 0};

        while (!pq.empty()) 
        {
            auto [d, r, c] = pq.top();
            pq.pop();

            if (r == destination[0] && c == destination[1])
                return d;

            // popped distance is larger than already calcualted distance then no no need to explore 
            if (d > dist[r][c]) continue;  // Skip if this is an outdated path

            for (int i = 0; i < 4; ++i) {
                int nr = r, nc = c, steps = 0;

                // Keep rolling in the current direction until hitting a wall
                while (nr + dr[i] >= 0 && nr + dr[i] < rows &&
                       nc + dc[i] >= 0 && nc + dc[i] < cols &&
                       maze[nr + dr[i]][nc + dc[i]] == 0) 
                {
                    nr += dr[i];
                    nc += dc[i];
                    steps++;
                }

                if ( dist[nr][nc] > (d + steps)) 
                {
                    dist[nr][nc] = d + steps;
                    pq.push({dist[nr][nc], nr, nc});
                }
            }
        }

        return -1;
    }
};

/*
Short approach (Dijkstra with array<int,3>):
- Use Dijkstra's algorithm with a min-heap storing {distance, row, col}.
- From each cell, roll in each direction until a wall and count the steps.
- If the new total distance is less than current, update and push.
- Return the shortest distance to the destination if reachable, else -1.
*/
