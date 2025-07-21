class Solution 
{
public:

    int countPairs(vector<vector<int>>& coordinates, int k) 
    {
        map<pair<int, int>, int> freq;
        long long totalPairs = 0;

        for (auto& point : coordinates) 
        {
            int x1 = point[0];
            int y1 = point[1];

            // Try all j from 0 to k such that:
            //      (x1 ^ x2) + (y1 ^ y2) == k
            // Then we can partition k into:
            //      j = (x1 ^ x2), and (k - j) = (y1 ^ y2)
            // => x2 = x1 ^ j, y2 = y1 ^ (k - j)

            for (int j = 0; j <= k; j++) 
            {
                int x2 = x1 ^ j;
                int y2 = y1 ^ (k - j);

                if (freq.count({x2, y2})) 
                {
                    totalPairs += freq[{x2, y2}];
                }
            }

            freq[{x1, y1}]++;
        }

        return totalPairs;
    }
};

/*

APPROACH:
---------
We are given a list of points, and we want to count how many **unordered pairs** (i, j) exist such that:

    (x1 ^ x2) + (y1 ^ y2) == k

Where:
- (x1, y1) is the current point
- (x2, y2) is a previously seen point (to avoid duplicate counting)

### Key Observations:
---------------------------------
1. The constraint 0 <= k <= 100 lets us brute-force over all possible partitions of `k` as:
       k = j + (k - j) for j in [0...k]

2. From the equation:
       (x1 ^ x2) + (y1 ^ y2) = k
       let say (x1 ^ x2) = j , so automatically , (y1^y2) = k - j
        → x2 = x1 ^ j             => very important Property
        → y2 = y1 ^ (k - j)       => very important Property

   This means: for each j in [0, k], we compute what x2 and y2 must be, and then simply check if such a point exists in our frequency map.

3. This gives us an **O(n * k)** solution since for each point we try k partitions.

---

DRY RUN:
--------
Input:
    points = [ [1,2], [2,0], [2,3] ]
    k = 2

Let’s iterate:
  - First point: (1,2)
    No prior points → freq = {}

  - Second point: (2,0)
    Try j = 0 → x2 = 2^0=2, y2=0^2=2 → (2,2) not in map
    Try j = 1 → x2 = 2^1=3, y2=0^1=1 → (3,1) not in map
    Try j = 2 → x2 = 2^2=0, y2=0^0=0 → (0,0) not in map
    → no match found
    → freq[(2,0)] = 1

  - Third point: (2,3)
    Try j = 0 → x2 = 2^0=2, y2=3^2=1 → (2,1) not in map
    Try j = 1 → x2 = 2^1=3, y2=3^1=2 → (3,2) not in map
    Try j = 2 → x2 = 2^2=0, y2=3^0=3 → (0,3) not in map
    → no match found
    → freq[(2,3)] = 1

→ Final count = 0

---

TIME COMPLEXITY:
-----------------
Let:
- `n` = number of points
- `k` ≤ 100 (small)

Then:
- Outer loop runs n times
- Inner loop runs (k+1) times

→ Total Time = **O(n * k)**  
→ Map lookups take O(1) amortized (or O(log n) worst case for `map`, can use `unordered_map` for better performance)

---

SPACE COMPLEXITY:
------------------
- We store at most n unique points → **O(n)** space for the map

*/
