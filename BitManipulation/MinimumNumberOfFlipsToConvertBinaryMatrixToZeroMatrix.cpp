class Solution 
{
    // To keep track of visited matrix states
    map<vector<vector<int>>, int> visited;

public:
    int minFlips(vector<vector<int>>& mat) 
    {
        if (mat.empty())
            return -1;

        int steps = 0;
        queue<vector<vector<int>>> q;

        // Start BFS with initial matrix
        q.push(mat);
        visited[mat] = 1;

        while (!q.empty()) 
        {
            int levelSize = q.size();
            while (levelSize--) 
            {
                vector<vector<int>> current = q.front();
                q.pop();

                if (isAllZero(current))
                    return steps;

                int rows = current.size();
                int cols = current[0].size();

                // Try flipping every cell
                for (int i = 0; i < rows; ++i) 
                {
                    for (int j = 0; j < cols; ++j) 
                    {
                        vector<vector<int>> next = current;
                        flip(next, i, j);

                        if (!visited[next]) 
                        {
                            visited[next] = 1;
                            q.push(next);
                        }
                    }
                }
            }
            steps++;
        }

        return -1; // Impossible to convert to all 0s
    }

    // Helper to check if all elements are 0
    bool isAllZero(const vector<vector<int>>& mat) 
    {
        for (auto& row : mat)
            for (int val : row)
                if (val)
                    return false;
        return true;
    }

    // Flip cell (i,j) and its 4-directional neighbors
    void flip(vector<vector<int>>& mat, int i, int j) 
    {
        int rows = mat.size();
        int cols = mat[0].size();

        mat[i][j] ^= 1;
        if (i > 0) mat[i - 1][j] ^= 1;
        if (j > 0) mat[i][j - 1] ^= 1;
        if (i + 1 < rows) mat[i + 1][j] ^= 1;
        if (j + 1 < cols) mat[i][j + 1] ^= 1;
    }
};


/*

🧠 Approach:
-----------
- This is a classic **state-space search** problem where each state is a binary matrix.
- The goal is to reach the state where **all values are 0**.
- Each **flip** toggles the current cell and its 4 neighbors (up/down/left/right).
- Use **BFS** to find the **minimum number of flips** (shortest path).

🔁 BFS:
- Each matrix configuration is a node.
- Each flip is an edge to a new configuration.
- Use a queue to explore each possible flip state level-by-level.

📌 Key Details:
- Store visited matrices in a map to prevent revisiting.
- Use `flip()` function to simulate each flip operation.

⏱ Time Complexity:
- There are at most `2^(m*n)` different matrices (each cell has 2 states)
- For small grids (like 3x3), that’s at most `512` states.
- So the BFS is efficient for small grids.

📦 Space Complexity:
- O(2^(m*n)) for storing visited matrix states in the map.

Example:
---------
Input:
mat = [
  [0,0],
  [0,1]
]

Flipping cell (1,1):
→ changes (1,1), (0,1), (1,0) → reaches all zero.

Answer: 1

*/
