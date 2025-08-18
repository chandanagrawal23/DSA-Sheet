#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int largest1BorderedSquare(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();

        // Precompute horizontal and vertical runs of 1s
        vector<vector<int>> rightToLeftOnes(n, vector<int>(m, 0));
        vector<vector<int>> downToTopOnes(n, vector<int>(m, 0));

        // Fill rightToLeftOnes (continuous 1's from right to left)
        // Fill downToTopOnes (continuous 1's from top to bottom)
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (grid[i][j] == 1)
                {
                    rightToLeftOnes[i][j] = 1 + (j + 1 < m ? rightToLeftOnes[i][j + 1] : 0);
                    downToTopOnes[i][j] = 1 + (i + 1 < n ? downToTopOnes[i + 1][j] : 0);
                }
            }
        }

        // Try the largest possible square side first (greedy)
        for (int k = min(n, m); k >= 1; k--)
        {
            for (int i = 0; i + k - 1 < n; i++)
            {
                for (int j = 0; j + k - 1 < m; j++)
                {
                    // Check 4 borders of the square of side k
                    int topBorder = rightToLeftOnes[i][j];
                    int bottomBorder = rightToLeftOnes[i + k - 1][j];
                    int leftBorder = downToTopOnes[i][j];
                    int rightBorder = downToTopOnes[i][j + k - 1];

                    if (topBorder >= k && bottomBorder >= k &&
                        leftBorder >= k && rightBorder >= k)
                    {
                        return k * k; // Found largest area immediately
                    }
                }
            }
        }
        return 0;
    }
};


#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int largest1BorderedSquare(vector<vector<int>> &grid)
    {
        int n = grid.size(), m = grid[0].size();

        // Precompute horizontal and vertical runs of 1s
        vector<vector<int>> rightToLeftOnes(n, vector<int>(m, 0));
        vector<vector<int>> downToTopOnes(n, vector<int>(m, 0));

        // Fill rightToLeftOnes (continuous 1's from right to left)
        // Fill downToTopOnes (continuous 1's downward starting at (i,j))
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (grid[i][j] == 1)
                {
                    rightToLeftOnes[i][j] = 1 + (j + 1 < m ? rightToLeftOnes[i][j + 1] : 0);
                    downToTopOnes[i][j] = 1 + (i + 1 < n ? downToTopOnes[i + 1][j] : 0);
                }
            }
        }

        // Try the largest possible square side first (greedy)
        for (int k = min(n, m); k >= 1; k--)
        {
            for (int i = 0; i + k - 1 < n; i++)
            {
                for (int j = 0; j + k - 1 < m; j++)
                {
                    // Check 4 borders of the square of side k
                    int topBorder    = rightToLeftOnes[i][j];
                    int bottomBorder = rightToLeftOnes[i + k - 1][j];
                    int leftBorder   = downToTopOnes[i][j];
                    int rightBorder  = downToTopOnes[i][j + k - 1];

                    if (topBorder >= k && bottomBorder >= k &&
                        leftBorder >= k && rightBorder >= k)
                    {
                        return k * k; // Found largest area immediately
                    }
                }
            }
        }
        return 0;
    }
};


/*
Approach (with Detailed Dry Run on a 5x5 "big" example)
------------------------------------------------------

Goal:
-----
Return the area of the largest square whose 4 borders are all 1's.

Key Idea:
---------
Precompute two DP tables so we can check any square's 4 borders in O(1):

1) rightToLeftOnes[i][j]:
   Number of consecutive 1's starting at (i,j) going from right to left".
   (We compute it by scanning from right to left.)
2) downToTopOnes[i][j]:
   Number of consecutive 1's starting at (i,j) going from down to top.
   (We compute it by scanning from bottom to top.)

Then, for any candidate square with top-left (i,j) and side k:
- Top border is all 1's  iff  rightToLeftOnes[i][j]         >= k
- Bottom border is all 1's iff  rightToLeftOnes[i+k-1][j]    >= k
- Left border is all 1's  iff  downToTopOnes[i][j]           >= k
- Right border is all 1's iff  downToTopOnes[i][j+k-1]       >= k

We search k from large to small; the first valid square we find is optimal.

----------------------------------------------------------------------
Dry Run on a "big" 5x5 grid
----------------------------------------------------------------------
Let:

grid =
1 1 1 0 1
1 0 1 1 1
1 1 1 1 1
1 1 1 1 1
0 1 1 1 1

Step A: Build DP tables (scan from bottom-right to top-left)
------------------------------------------------------------
Rule:
- If grid[i][j] == 1:
    rightToLeftOnes[i][j] = 1 + rightToLeftOnes[i][j+1] (if j+1 in range else 0)
    downToTopOnes[i][j]   = 1 + downToTopOnes[i+1][j]   (if i+1 in range else 0)
- Else 0.

Selected cell-by-cell examples:
- Cell (4,4)=1:
    rightToLeftOnes[4][4]=1, downToTopOnes[4][4]=1
- Cell (4,3)=1:
    rightToLeftOnes[4][3]=1+rightToLeftOnes[4][4]=2,  downToTopOnes[4][3]=1
- Cell (4,1)=1:
    rightToLeftOnes[4][1]=1+rightToLeftOnes[4][2]=1+3=4, downToTopOnes[4][1]=1
- Cell (0,0)=1, looking right/down:
    rightToLeftOnes[0][0]=1+rightToLeftOnes[0][1]=1+2=3,
    downToTopOnes[0][0]=1+downToTopOnes[1][0]=1+3=4

After completing all cells, full tables are:

rightToLeftOnes (runs of 1's to the right from (i,j)):
Row 0: [3, 2, 1, 0, 1]
Row 1: [1, 0, 3, 2, 1]
Row 2: [5, 4, 3, 2, 1]
Row 3: [5, 4, 3, 2, 1]
Row 4: [0, 4, 3, 2, 1]

downToTopOnes (runs of 1's down from (i,j)):
Row 0: [4, 1, 5, 0, 5]
Row 1: [3, 0, 4, 4, 4]
Row 2: [2, 3, 3, 3, 3]
Row 3: [1, 2, 2, 2, 2]
Row 4: [0, 1, 1, 1, 1]

Step B: Try candidate squares from largest k downwards
------------------------------------------------------

k = 5:
- Only top-left (0,0) fits. Check borders:
  topBorder    = rightToLeftOnes[0][0] = 3   (< 5)  → FAIL immediately.
  So no 5x5 possible.

k = 4:
Possible top-lefts: (0,0),(0,1),(1,0),(1,1)
- (0,0): topBorder=3 < 4 → FAIL
- (0,1): topBorder=2 < 4 → FAIL
- (1,0): topBorder=1 < 4 → FAIL
- (1,1): topBorder=0 < 4 → FAIL
No 4x4 exists.

k = 3:
Check (0,0) first (since we scan in row-major):
- topBorder    = rightToLeftOnes[0][0] = 3   (OK)
- bottomBorder = rightToLeftOnes[2][0] = 3   (OK)
- leftBorder   = downToTopOnes[0][0]   = 4   (>=3 OK)
- rightBorder  = downToTopOnes[0][2]   = 5   (>=3 OK)

All 4 borders meet the threshold → 3x3 square is VALID at (0,0).
Since we search from largest k to smallest, we "return area = 3*3 = 9".

(For intuition, that 3x3 square covers rows 0..2 and cols 0..2:
 top row 111, bottom row 111, left col [1,1,1], right col [1,1,1].)

We stop here; the first found is the largest.

----------------------------------------------------------------------
Why both DP tables?
-------------------
If we only used the horizontal table, a row like "1 1 1 1" could trick us into
believing a big square exists, even if some vertical border includes a zero.
The vertical DP (`downToTopOnes`) guarantees the two side borders are also all 1's.

Complexity:
-----------
- Precomputation: O(N*M)
- Checking: In worst-case we test O(N*M) positions for each k in [min(N,M)..1],
            so O(N*M*min(N,M)) in the worst case.
  (Early exit helps in practice.)
- Space: O(N*M) for the two DP tables.

*/

/**************** IMPORTANT ********************
 Binary Search will not work for this problem, because:
==========================================================

Binary Search assumes monotonicity:
- If a square of side = k exists, then all smaller sides (< k) must also exist.
- If a square of side = k does not exist, then no larger side (> k) can exist.

But here this monotonic property does not hold.

Example:
grid = [[1,1,1],
        [1,0,1],
        [1,1,1]]

- 1x1 square exists ✅
- 2x2 square does NOT exist ❌
- 3x3 square exists ✅

So there can be "gaps", hence Binary Search will fail.
*/
