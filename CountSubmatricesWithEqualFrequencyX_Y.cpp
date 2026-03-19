class Solution 
{
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // prefix count of X and Y
        vector<vector<int>> prefixX(rows + 1, vector<int>(cols + 1, 0));
        vector<vector<int>> prefixY(rows + 1, vector<int>(cols + 1, 0));

        int validSubmatrices = 0;

        for (int r = 1; r <= rows; r++) 
        {
            for (int c = 1; c <= cols; c++) 
            {
                // build prefix sums
                prefixX[r][c] = prefixX[r - 1][c] + prefixX[r][c - 1] - prefixX[r - 1][c - 1];
                prefixY[r][c] = prefixY[r - 1][c] + prefixY[r][c - 1] - prefixY[r - 1][c - 1];

                // update based on current cell
                if (grid[r - 1][c - 1] == 'X') 
                {
                    prefixX[r][c]++;
                } 
                else if (grid[r - 1][c - 1] == 'Y') 
                {
                    prefixY[r][c]++;
                }

                // check condition
                if (prefixX[r][c] > 0 && prefixX[r][c] == prefixY[r][c]) 
                {
                    validSubmatrices++;
                }
            }
        }

        return validSubmatrices;
    }
};

/*
APPROACH:

We use 2D prefix sum to count occurrences of 'X' and 'Y' in submatrices 
from (0,0) to (r,c).

1. prefixX[r][c] → number of 'X' in rectangle (0,0) → (r-1,c-1)
2. prefixY[r][c] → number of 'Y' in rectangle (0,0) → (r-1,c-1)

At every cell (r,c):
- We build prefix sums using standard 2D prefix formula:
  top + left - overlap

- Then we update based on current grid cell.

- If:
    prefixX > 0  AND  prefixX == prefixY
  → this submatrix (0,0 to r,c) is valid.

We count all such valid submatrices.

Time Complexity:
O(rows * cols)

Space Complexity:
O(rows * cols)
*/
