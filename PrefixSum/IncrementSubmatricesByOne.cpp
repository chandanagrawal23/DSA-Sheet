#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries)
    {
        // Create a (n+1)x(n+1) 2D difference array initialized with 0
        vector<vector<int>> diff(n + 1, vector<int>(n + 1, 0));

        // Apply each query as a 2D range update using 4-point marking
        for (auto &q : queries)
        {
            int r1 = q[0];
            int c1 = q[1];
            int r2 = q[2];
            int c2 = q[3];

            // Start adding 1 from (r1, c1)
            diff[r1][c1] += 1;

            // Cancel the addition beyond right column
            if (c2 + 1 < n)
            {
                diff[r1][c2 + 1] -= 1;
            }

            // Cancel the addition beyond bottom row
            if (r2 + 1 < n)
            {
                diff[r2 + 1][c1] -= 1;
            }

            // Adjust for double cancellation at bottom-right corner
            if (r2 + 1 < n && c2 + 1 < n)
            {
                diff[r2 + 1][c2 + 1] += 1;
            }
        }

        // Convert difference array to actual matrix using 2D prefix sum
        vector<vector<int>> mat(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int val = diff[i][j];

                // Include top cell value
                if (i > 0)
                {
                    val += mat[i - 1][j];
                }

                // Include left cell value
                if (j > 0)
                {
                    val += mat[i][j - 1];
                }

                // Remove top-left cell to avoid double counting
                if (i > 0 && j > 0)
                {
                    val -= mat[i - 1][j - 1];
                }

                mat[i][j] = val;
            }
        }

        return mat;
    }
};


/*
Approach:
- We use a 2D Difference Array technique to apply multiple submatrix updates efficiently.

For each query [r1, c1, r2, c2]:
    → Add 1 at (r1, c1) to start the increment
    → Subtract 1 at (r1, c2+1) to cancel increment beyond right column
    → Subtract 1 at (r2+1, c1) to cancel increment beyond bottom row
    → Add 1 at (r2+1, c2+1) to fix double subtraction at bottom-right

Once all queries are applied, convert the diff matrix into final matrix using 2D prefix sum:
    → mat[i][j] = sum of diff[0..i][0..j] 
    → We build it using inclusion-exclusion logic:
        mat[i][j] = diff[i][j] + mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1]

Time Complexity: O(q + n^2)
- O(q) to apply q queries
- O(n^2) to compute prefix sum over n x n grid

Space Complexity: O(n^2)
- Extra matrix used for 2D diff and final result
*/
