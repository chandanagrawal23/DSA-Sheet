class Solution 
{
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int mod = 12345;

        vector<vector<int>> leftProduct(rows, vector<int>(cols));
        vector<vector<int>> rightProduct(rows, vector<int>(cols));
        vector<vector<int>> result(rows, vector<int>(cols));

        long long prefix = 1;

        // Left to right pass — storing product of all previous elements
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                leftProduct[i][j] = prefix;
                prefix = (prefix * grid[i][j]) % mod;
            }
        }

        prefix = 1;

        // Right to left pass — storing product of all next elements
        for (int i = rows - 1; i >= 0; i--) 
        {
            for (int j = cols - 1; j >= 0; j--) 
            {
                rightProduct[i][j] = prefix;
                prefix = (prefix * grid[i][j]) % mod;
            }
        }

        // Multiply left and right products for final result
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                long long product = 1LL * leftProduct[i][j] * rightProduct[i][j];
                result[i][j] = product % mod;
            }
        }

        return result;
    }
};

/*
Approach:
- Maintain two auxiliary matrices:
  1. `leftProduct[i][j]` stores product of all elements before (i,j)
  2. `rightProduct[i][j]` stores product of all elements after (i,j)
- Final answer for each cell is (product of all except current) = left * right
- Time: O(n * m)
- Space: O(n * m)
*/
