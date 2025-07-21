class Solution 
{
public:
    int countTrapezoids(vector<vector<int>>& points) 
    {
        const int MOD = 1e9 + 7;
        unordered_map<int, int> yCount;

        // Count how many points exist at each y-level
        for (const auto& pt : points) 
        {
            int y = pt[1];
            yCount[y]++;
        }

        // For each y-level with at least 2 points, compute nC2 combinations
        // and store it as (y, combinations)
        vector<pair<int, long long>> yPairs;

        for (const auto& [y, cnt] : yCount) 
        {
            if (cnt >= 2) 
            {
                long long comb = 1LL * cnt * (cnt - 1) / 2;
                yPairs.push_back({y, comb});
            }
        }

        int m = yPairs.size();
        vector<long long> suffixSum(m + 1, 0);

        // Build suffix sum from right to left
        for (int i = m - 1; i >= 0; i--) 
        {
            suffixSum[i] = (yPairs[i].second + suffixSum[i + 1]) % MOD;
        }

        // Compute final result using suffix sum to avoid O(m^2)
        long long result = 0;

        for (int i = 0; i < m - 1; i++) 
        {
            long long product = yPairs[i].second * suffixSum[i + 1] % MOD;
            result = (result + product) % MOD;
        }

        return result;
    }
};
/*
APPROACH:
---------
- A horizontal trapezoid is formed by selecting any two horizontal segments from different y-levels.
- A horizontal segment is valid if at least 2 points lie on the same horizontal line (i.e., same y-coordinate).
- From n points on the same y-level, we can choose (nC2) horizontal line segments.

- Let’s say we have m such y-levels (where each has ≥2 points).
- For each such level i, let ways[i] = number of horizontal segments = nC2.

- The total trapezoids formed = sum of all ways[i] * ways[j] for i < j

Instead of using 2 nested loops (O(m^2)), we apply suffix sum optimization:
- Precompute suffixSum[i+1] = ways[i+1] + ways[i+2] + ... + ways[m-1]
- Then result += ways[i] * suffixSum[i+1] for all i from 0 to m-2

This reduces the complexity from O(m²) to O(m)

EXAMPLE (Dry Run):
------------------
Input points:
[ [1,0], [2,0], [3,0], [4,0],        → y = 0 → 4 pts → 4C2 = 6
  [1,1], [2,1], [3,1],              → y = 1 → 3 pts → 3C2 = 3
  [2,3], [3,3],                     → y = 3 → 2 pts → 2C2 = 1
  [1,5], [2,5], [3,5], [4,5] ]      → y = 5 → 4 pts → 4C2 = 6

Valid levels: y = 0, 1, 3, 5
ways = [6, 3, 1, 6]

Brute force pairwise combinations:
(0,1): 6*3 = 18
(0,3): 6*1 = 6
(0,5): 6*6 = 36
(1,3): 3*1 = 3
(1,5): 3*6 = 18
(3,5): 1*6 = 6
Total = 87

Suffix sum:
suffix[3] = 6
suffix[2] = 1 + 6 = 7
suffix[1] = 3 + 7 = 10
suffix[0] = 6 + 10 = 16

Optimized result:
6 * 10 = 60
3 * 7  = 21
1 * 6  = 6
Total = 87 ✔️

LARGE SCALE SCENARIO:
---------------------
If we have 10 y-levels, each with 100 points:
- Each level → 100C2 = 4950 segments
- Total trapezoids = 10C2 * (4950 * 4950) = 45 * 24,502,500 = 1,102,612,500
- Final answer = (1,102,612,500 mod 1e9+7) = 102612493

Even for huge input sizes (up to 10^5 points), our approach runs in linear time relative to input.

TIME COMPLEXITY:
----------------
- O(n) to group points by y-coordinate
- O(m) to compute combinations and suffix sum (m = number of y-levels with ≥2 points)

SPACE COMPLEXITY:
-----------------
- O(m) to store y-level combinations and suffix sums
*/
