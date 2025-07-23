class NumMatrix
{
public:
    vector<vector<int>> sum;

    NumMatrix(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();

        // sum[i][j] stores prefix sum from (0,0) to (i-1,j-1) in original matrix
        sum = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // Prefix sum formula (inclusion-exclusion)
                sum[i][j] = sum[i - 1][j]          // upper block
                          + sum[i][j - 1]          // left block
                          - sum[i - 1][j - 1]      // remove overlap
                          + matrix[i - 1][j - 1];  // current cell
            }
        }
    }

    int sumRegion(int r1, int c1, int r2, int c2)
    {
        // Shift everything by +1 due to prefix array starting from index 1
        r1++, c1++, r2++, c2++;

        // Return sum of submatrix from (r1, c1) to (r2, c2) using inclusion-exclusion
        return sum[r2][c2]
             - sum[r1 - 1][c2]
             - sum[r2][c1 - 1]
             + sum[r1 - 1][c1 - 1];
    }
};

/*
Approach:

We use the 2D Prefix Sum technique to compute region sums in O(1) time.

1. Prefix Sum Grid (sum[i][j]):
   - sum[i][j] stores the sum of the submatrix from (0,0) to (i-1,j-1) in the original matrix.
   - We use size (m+1 x n+1) to simplify boundary handling (1-based indexing).

To calculate sums, the ideas as below
=====================================

+-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
|     | |       |     |        |     |     |     |         |     |     |        |
|     | |       |     |        |     |     |     |         |     |     |        |
+-----+-+       |     +--------+     |     |     |         |     +-----+        |
|     | |       |  =  |              |  +  |     |         |  -  |              |
+-----+-+       |     |              |     +-----+         |     |              |
|               |     |              |     |               |     |              |
|               |     |              |     |               |     |              |
+---------------+     +--------------+     +---------------+     +--------------+

   sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]     + matrix[i-1][j-1] ( current Cell)

So, we use the same idea to find the specific area's sum.
===========================================================

+---------------+   +---------+----+   +---+-----------+   +---------+----+   +---+----------+
|               |   |         |    |   |   |           |   |         |    |   |   |          |
|   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
|   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
|   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
|   |      |    |   |         |    |   |   |           |   |              |   |              |
|   +------+    |   +---------+    |   +---+           |   |              |   |              |
|        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+


2. Building the Prefix Grid (constructor):
   - For each cell (i, j), total sum includes:
       a. sum[i-1][j]: sum of the top region
       b. sum[i][j-1]: sum of the left region
       c. subtract sum[i-1][j-1] to avoid double counting overlap
       d. add current matrix[i-1][j-1]

3. Querying sumRegion(r1, c1, r2, c2):
   - To get sum from (r1,c1) to (r2,c2), we apply:
     → total = sum[r2][c2]
              - sum[r1-1][c2]
              - sum[r2][c1-1]
              + sum[r1-1][c1-1]
   - This formula removes the regions outside the desired rectangle and adds back the overlapping subtracted area.

4. Time Complexity:
   - Constructor (preprocessing): O(m * n)
   - sumRegion(): O(1) — Constant time due to precomputation

5. Space Complexity: O(m * n)
   - We use a 2D array of size (m+1 x n+1)

This approach allows us to handle up to 10^4 queries efficiently.

*/
