class Solution 
{
public:
    int maxRectangleArea(vector<vector<int>>& points) 
    {
        const int SHIFT = 1 << 10;  // Safe for coordinates ≤ 1000
        set<int> pointSet;

        // Encode all points into a hashable integer key
        for (auto& p : points) 
        {
            pointSet.insert(p[0] * SHIFT + p[1]);
        }

        int n = points.size();
        int maxArea = -1;

        // Try every pair of points as diagonal corners of a rectangle
        for (int i = 0; i < n; ++i) 
        {
            int x1 = points[i][0], y1 = points[i][1];

            for (int j = i + 1; j < n; ++j) 
            {
                int x2 = points[j][0], y2 = points[j][1];

                // Ensure points (x1, y1) and (x2, y2) form a diagonal
                if (x1 != x2 && y1 != y2) 
                {
                    // The other two rectangle corners will be (x1, y2) and (x2, y1)
                    if (pointSet.count(x1 * SHIFT + y2) &&
                        pointSet.count(x2 * SHIFT + y1)) 
                    {
                        // Validate that no extra point lies inside or on border
                        if (isRectangleEmpty(x1, y1, x2, y2, pointSet, points)) 
                        {
                            int area = abs(x1 - x2) * abs(y1 - y2);
                            maxArea = max(maxArea, area);
                        }
                    }
                }
            }
        }

        return maxArea;
    }

private:
    // Checks if any point (other than the 4 corners) lies inside or on the rectangle
    bool isRectangleEmpty(int x1, int y1, int x2, int y2, set<int>& pointSet, vector<vector<int>>& points)
    {
        int minX = min(x1, x2), maxX = max(x1, x2);
        int minY = min(y1, y2), maxY = max(y1, y2);

        for (auto& p : points) 
        {
            int x = p[0], y = p[1];

            // Skip the four rectangle corners: (x1,y1), (x2,y2), (x1,y2), (x2,y1)
            if ((x == x1 && y == y1) || (x == x2 && y == y2) ||
                (x == x1 && y == y2) || (x == x2 && y == y1))
                continue;

            // If point lies inside or on border, it's invalid
            if (x >= minX && x <= maxX && y >= minY && y <= maxY) 
            {
                return false;
            }
        }

        return true;
    }
};

/*
🔍 Approach:
- For every pair of points (x1, y1), (x2, y2) such that x1 ≠ x2 and y1 ≠ y2, treat them as diagonally opposite corners.
- The other two corners of the rectangle are (x1, y2) and (x2, y1). All four corners must exist in the input.
- Then, check that no other point lies inside or on the edges of the rectangle using `isRectangleEmpty()`.

🕒 Time Complexity: O(n^3) — checking every pair of points and then scanning all points for each rectangle.
🧠 Space Complexity: O(n) — for storing the encoded points in a set.


//extension of this nice problem  :https://leetcode.com/problems/minimum-area-rectangle/

*/
