class Solution {
public:
    // Function to check if a point (x, y) lies inside or on a circle
    bool isInside(int circle_x, int circle_y, int rad, int x, int y) {
        // Use squared distance to avoid square root for efficiency
        return ( (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) )  <= (rad * rad);
    }

    // Main function to count number of points inside each circle
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> ans;

        // For each query circle
        for (auto& circle : queries) {
            int x = circle[0];  // circle center x
            int y = circle[1];  // circle center y
            int r = circle[2];  // circle radius
            int cnt = 0;

            // Check each point whether it lies inside this circle
            for (auto& coordinate : points) {
                // Increment count if the point is inside or on the circle
                cnt += isInside(x, y, r, coordinate[0], coordinate[1]);
            }

            // Store the result for this query
            ans.push_back(cnt);
        }

        return ans;
    }
};

/*
Approach:
---------
1. For each query (which represents a circle defined by center (x, y) and radius r), 
   we want to count how many given points lie inside or on the circle.

2. To check if a point (px, py) lies inside or on a circle centered at (cx, cy) with radius r,
   we use the condition:
       (px - cx)^2 + (py - cy)^2 <= r^2

   Why does this work?
   -------------------
   - The actual distance between the point and the circle's center is:
         distance = sqrt((px - cx)^2 + (py - cy)^2)
   - To be inside or on the circle, the distance must be ≤ r (radius).
   - So the condition becomes:
         sqrt((px - cx)^2 + (py - cy)^2) ≤ r

   - Squaring both sides to eliminate the square root (to avoid the expensive sqrt operation):
         (px - cx)^2 + (py - cy)^2 ≤ r^2

   - This squared form is **mathematically equivalent** and much **faster** to compute
     because it avoids the floating-point sqrt() function, which is costly and unnecessary
     for just comparing distances.

   - It's also more accurate for integer inputs, avoiding precision issues that might come
     with floating-point calculations.

3. We iterate over each query and for each, check every point to see if it satisfies 
   the condition using the helper function `isInside`.

4. Time Complexity:
   - Let q = number of queries (circles), and p = number of points.
   - For each of the q queries, we check all p points → O(q * p)

5. This brute-force approach is acceptable when the number of queries and points is small
   (e.g., both under 500), which is the case in the original Leetcode problem.

6. The final result is a vector where each entry represents the count of points inside
   the respective circle from the queries list.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Approach 2 , more optimised better than above, instead of iterating to each point , 
//              we will find first point which "MAY" lie inside the current circle,
//              same will find last point which "MAY" lie inside circle
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        sort(points.begin(), points.end());
        vector<int> ans;

        for (auto& q : queries) {
            int cx = q[0], cy = q[1], r = q[2];
            int r2 = r * r;

            // Get x-range [startIndex, endIndex] using binary search
            int start = lowerBoundX(points, cx - r); // Binary search for first point with x >= (cx - r)
            int end   = upperBoundX(points, cx + r); // Binary search for last point with x <= (cx + r)

            int count = 0;
            for (int i = start; i <= end; ++i) 
            {
                int dx = points[i][0] - cx;
                int dy = points[i][1] - cy;
                 // if distance of point from circle centre is less than equal r , means inside  circle
                if (dx * dx + dy * dy <= r2)
                    count++;
            }

            ans.push_back(count);
        }

        return ans;
    }

private:
    // Find first index where x >= target
    int lowerBoundX(const vector<vector<int>>& points, int target) {
        int l = 0, h = points.size() - 1, ans = points.size();
        while (l <= h) {
            int mid = (l + h) / 2;
            if (points[mid][0] >= target) {
                ans = mid;
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }

    // Find last index where x <= target
    int upperBoundX(const vector<vector<int>>& points, int target) {
        int l = 0, h = points.size() - 1, ans = -1;
        while (l <= h) {
            int mid = (l + h) / 2;
            if (points[mid][0] <= target) {
                ans = mid;
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
        return ans;
    }
};
/*
Approach:
---------
- Sort the points based on x-coordinate.
- For each query (circle center cx, cy and radius r):
   1. Only consider points whose x is in [cx - r, cx + r] (because if x is outside this range, point can’t be inside circle).
   2. Use binary search to find that valid range.
   3. For those points, check full (x, y) Euclidean distance using (dx² + dy²) ≤ r².

Time Complexity:
----------------
- Sorting points: O(n log n)
- For each query:
   - Binary search: O(log n)
   - Loop over filtered points (say k): O(k)
- So total is O(n log n + q × log n + total_filtered_points)

Why better than brute-force:
----------------------------
- Brute-force does O(n * q)
- This filters only relevant x-range points per query using binary search.
*/


// there is one more K-D tree approach which is out of scope for this 
