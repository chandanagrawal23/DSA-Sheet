#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
    {
        int rows = maze.size();
        int cols = maze[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        // move vectors: down, right, up, left
        vector<int> dr = {1, 0, -1, 0};
        vector<int> dc = {0, 1, 0, -1};

        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        visited[start[0]][start[1]] = true;

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            if (r == destination[0] && c == destination[1])
                return true;

            for (int d = 0; d < 4; ++d)
            {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // roll in direction d until we hit a wall
                while (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] == 0)
                {
                    nr += dr[d];
                    nc += dc[d];
                }

                // step back to last valid position
                nr -= dr[d];
                nc -= dc[d];

                if (!visited[nr][nc])
                {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return false;
    }
};

/*
Short approach:
1. Use BFS starting from the ball’s initial coordinates.
2. For each cell, roll the ball in all four directions until it hits a wall
   (keep advancing while inside bounds and on 0’s).
3. The last valid cell before the wall becomes a new BFS node.
4. Track visited stop-points to avoid repeats.
5. Succeed as soon as the destination cell is dequeued; if the queue empties,
   no path exists.  Time/space: O(m·n).
*/
