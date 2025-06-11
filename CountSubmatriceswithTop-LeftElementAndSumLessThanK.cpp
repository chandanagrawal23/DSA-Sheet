class Solution 
{
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) 
    {
        int n = grid.size(), m = grid[0].size();
        int cnt = 0;
        vector<vector<int>> prefixSum(n, vector<int>(m));

        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                prefixSum[i][j] = grid[i][j];

                // Add left cell value
                if (j >= 1)
                    prefixSum[i][j] += prefixSum[i][j - 1];

                // Add top cell value
                if (i >= 1)
                    prefixSum[i][j] += prefixSum[i - 1][j];

                // Subtract overlap (top-left) to avoid double-counting
                if (i >= 1 && j >= 1)
                    prefixSum[i][j] -= prefixSum[i - 1][j - 1];

                // Count if current prefix sum is ≤ k
                if (prefixSum[i][j] <= k)
                    cnt++;
            }
        }

        return cnt;
    }
};

/*
Approach:
- Build a separate 2D prefixSum array where each prefixSum[i][j] stores sum of submatrix (0,0) to (i,j)
- Use inclusion-exclusion to calculate prefixSum:
    prefixSum[i][j] = grid[i][j] + prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1]
  We subtract prefixSum[i-1][j-1] because it gets counted twice when we add prefixSum[i-1][j] and prefixSum[i][j-1]

- Count all positions where prefixSum[i][j] ≤ k

Time: O(n * m)
Space: O(n * m) for prefix sum grid
*/
