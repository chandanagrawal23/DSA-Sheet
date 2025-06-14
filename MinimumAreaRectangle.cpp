class Solution 
{
public:
    int minAreaRect(vector<vector<int>>& points) 
    {
        set<int> pointSet;
        
        // Store points as unique integers (x * 2^10 + y)
        for (auto& p : points) 
        {
            pointSet.insert(p[0] * (1 << 10) + p[1]);
        }

        int n = points.size();
        int minArea = INT_MAX;

        // Try every pair of points as opposite corners of rectangle
        for (int i = 0; i < n; ++i) 
        {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) 
            {
                int x2 = points[j][0], y2 = points[j][1];

                // Check if they can form a valid rectangle (diagonally opposite)
                if (x1 != x2 && y1 != y2) 
                {
                    // Check if the other two corners exist
                    if (pointSet.count(x1 * (1 << 10) + y2) &&
                        pointSet.count(x2 * (1 << 10) + y1)) 
                    {
                        int area = abs(x1 - x2) * abs(y1 - y2);
                        minArea = min(minArea, area);
                    }
                }
            }
        }

        return (minArea == INT_MAX) ? 0 : minArea;
    }
};

/*
Approach:

- Treat every pair of points as potential diagonals of a rectangle.
- For a valid rectangle, the other two corners must also exist in the point set.
- Use a hashable encoding (x * 2^10 + y) to store and lookup 2D points efficiently.
- For each valid rectangle, calculate the area and track the minimum.

Time: O(n^2) for all pairs.
Space: O(n) for storing encoded points.
*/
