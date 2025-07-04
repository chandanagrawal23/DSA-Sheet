class Solution 
{
public:

    // Directions for up, down, left, right
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) 
    {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<int>> dist(rows, vector<int>(cols, -1));  // Distance matrix
        queue<pair<int, int>> bfsQueue;

        // Step 1: Push all 0s into the queue as BFS starting points
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                if (mat[i][j] == 0) 
                {
                    dist[i][j] = 0;
                    bfsQueue.push({i, j});
                }
            }
        }

        // Step 2: Perform multi-source BFS from all 0s
        while (!bfsQueue.empty()) 
        {
            auto [currRow, currCol] = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < 4; i++) 
            {
                int newRow = currRow + dx[i];
                int newCol = currCol + dy[i];

                // Check bounds and whether the cell is unvisited
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && dist[newRow][newCol] == -1) 
                {
                    dist[newRow][newCol] = dist[currRow][currCol] + 1;
                    bfsQueue.push({newRow, newCol});
                }
            }
        }

        return dist;
    }
};

/*
Approach:
- We use a multi-source BFS to compute the shortest distance from each cell to the nearest 0.
- All 0s are added to the queue as starting points with distance 0.
- For each popped cell, we explore its 4 neighbors and update their distances if unvisited.

Time Complexity:  O(n * m), where n = rows, m = cols
Space Complexity: O(n * m), for distance matrix and BFS queue
*/
