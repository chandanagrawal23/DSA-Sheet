#include <vector>
#include <deque>

using namespace std;

class Solution 
{
public:
    bool isReachable(vector<vector<int>>& grid, int health) 
    {
        int m = grid.size();
        int n = grid[0].size();

        // Directions: right, left, down, up
        vector<pair<int, int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};

        // Distance matrix to store minimum health used to reach each cell
        vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
        deque<pair<int, int>> dq;

        dq.push_front({0, 0});
        cost[0][0] = grid[0][0];  // 1 if unsafe, 0 if safe

        while (!dq.empty()) 
        {
            auto [row, col] = dq.front();
            dq.pop_front();

            for (auto [dx, dy] : directions) 
            {
                int newRow = row + dx;
                int newCol = col + dy;

                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) 
                {
                    int newCost = cost[row][col] + grid[newRow][newCol];

                    if (newCost < cost[newRow][newCol]) 
                    {
                        cost[newRow][newCol] = newCost;

                        if (grid[newRow][newCol] == 1) 
                            dq.push_back({newRow, newCol});  // Unsafe move (cost 1)
                        else 
                            dq.push_front({newRow, newCol}); // Safe move (cost 0)
                    }
                }
            }
        }

        // Check if we reached bottom-right with enough remaining health
        return cost[m - 1][n - 1] < health;
    }
};

/*
 Approach:

- The grid has cells marked as `1` (unsafe → -1 health) or `0` (safe).
- We want to reach the destination `(m-1,n-1)` **with at least 1 health left**.
- Use **0-1 BFS** to calculate the minimum total cost (health loss) to reach any cell.
  - If moving to a `1`, add it to the **back** of the deque (costly step).
  - If moving to a `0`, add it to the **front** (free step).
- After the traversal, if the **minimum cost to reach (m-1, n-1)** is **< health**, return `true`.
  - That means we reached with at least 1 health remaining.
  - Else, return `false`.

 Time Complexity: O(m × n)
 Space Complexity: O(m × n)
*/
