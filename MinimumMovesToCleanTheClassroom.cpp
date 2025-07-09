class Solution
{
public:
    int minMoves(vector<string> &classroom, int energy)
    {
        int m = classroom.size(), n = classroom[0].size();

        vector<pair<int, int>> litters; // list of litter coordinates
        int startX = -1, startY = -1;   // starting coordinates

        // Directions: up, down, left, right
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};

        // Step 1: Find start and litter positions
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (classroom[i][j] == 'S')
                {
                    startX = i;
                    startY = j;
                }
                else if (classroom[i][j] == 'L')
                {
                    litters.push_back({i, j});
                }
            }
        }

        int totalL = litters.size();
        int allCollectedMask = (1 << totalL) - 1; // all bits set means all litters collected

        // Step 2: Initialize visited 4D array
        vector<vector<vector<vector<bool>>>> visited(
            m, vector<vector<vector<bool>>>(
                   n, vector<vector<bool>>(
                          energy + 1, vector<bool>(1 << totalL, false))));

        // Step 3: BFS queue — {x, y, energy, collected_mask, steps}
        queue<array<int, 5>> q;
        q.push({startX, startY, energy, 0, 0});
        visited[startX][startY][energy][0] = true;

        // Step 4: BFS traversal
        while (!q.empty())
        {
            auto state = q.front();
            q.pop();

            int x = state[0], y = state[1];
            int e = state[2], mask = state[3], steps = state[4];

            // If all litters collected, return the steps
            if (mask == allCollectedMask)
                return steps;

            // Try all 4 directions
            for (int d = 0; d < 4; ++d)
            {
                int nx = x + dx[d];
                int ny = y + dy[d];
                int new_energy = e - 1;

                // Skip invalid or blocked cells
                if (nx < 0 || ny < 0 || nx >= m || ny >= n || classroom[nx][ny] == 'X')
                    continue;

                // Can't move with 0 energy unless on 'R'
                if (new_energy < 0 && classroom[x][y] != 'R')
                    continue;

                // Recharge if stepping on 'R'
                if (classroom[nx][ny] == 'R')
                    new_energy = energy;

                // Update litter collection mask
                int new_mask = mask;
                for (int i = 0; i < totalL; ++i)
                {
                    if (litters[i].first == nx && litters[i].second == ny)
                    {
                        new_mask |= (1 << i); // collect the litter
                    }
                }

                // Enqueue new state if not visited
                if (!visited[nx][ny][new_energy][new_mask])
                {
                    visited[nx][ny][new_energy][new_mask] = true;
                    q.push({nx, ny, new_energy, new_mask, steps + 1});
                }
            }
        }

        // If we exit loop, it's not possible to collect all litters
        return -1;
    }
};

/*

  -----------------------------------
  APPROACH: Multi-State BFS + Bitmask
  -----------------------------------

  - We are given a grid where:
      'S' → Start position
      'L' → Litter to collect
      'R' → Recharge station (resets energy)
      'X' → Obstacle (impassable)
      '.' → Empty cell
  - Start with full energy and collect all 'L' using minimum steps.
  - Moving costs 1 energy; if energy is 0 and not on 'R', cannot move.
  - Use BFS where each state is defined by:
      (x, y, remaining_energy, collected_mask, steps_so_far)
  - Bitmask tracks which litters are collected.
  - Use a 4D visited array to avoid revisiting same state:
      visited[x][y][energy][mask]
  - Stop BFS and return steps when all litters are collected.

  
    TIME COMPLEXITY: O(m * n * energy * 2^L), where L = number of litter cells (max ~15)
    SPACE COMPLEXITY: O(m * n * energy * 2^L) for visited states
    
*/
