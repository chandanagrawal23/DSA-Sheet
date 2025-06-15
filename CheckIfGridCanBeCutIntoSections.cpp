class Solution 
{
    // Extract all y-axis intervals [y1, y2] from rectangles
    vector<vector<int>> extractYAxisRanges(vector<vector<int>> &rects)
    {
        vector<vector<int>> yAxisRanges;

        for (auto &rect : rects)
        {
            // rect[1] = y1, rect[3] = y2
            yAxisRanges.push_back({rect[1], rect[3]});
        }

        return yAxisRanges;
    }

    // Extract all x-axis intervals [x1, x2] from rectangles
    vector<vector<int>> extractXAxisRanges(vector<vector<int>> &rects)
    {
        vector<vector<int>> xAxisRanges;

        for (auto &rect : rects)
        {
            // rect[0] = x1, rect[2] = x2
            xAxisRanges.push_back({rect[0], rect[2]});
        }

        return xAxisRanges;
    }

    // Check if we can find at least two non-overlapping intervals in 1D projection
    bool hasValidNonOverlappingCut(vector<vector<int>> &axisIntervals)
    {
        // Step 1: Sort the intervals by start point
        sort(axisIntervals.begin(), axisIntervals.end());

        int mergedEnd = axisIntervals[0][1]; // End of first interval
        int nonOverlapCount = 0;

        for (int i = 1; i < axisIntervals.size(); i++)
        {
            // If the current interval starts after the last merged end,
            // it means there's a gap => a valid cut can be made here
            if (axisIntervals[i][0] >= mergedEnd)
            {
                nonOverlapCount++; // Count how many such non-overlapping pieces we find
            }

            // Always extend the merged interval
            mergedEnd = max(mergedEnd, axisIntervals[i][1]);

            // If 2 or more non-overlapping parts found,
            // it means we can place a line that intersects at most one rectangle
            if (nonOverlapCount >= 2)
            {
                return true;
            }
        }

        return false;
    }

public:
    bool checkValidCuts(int n, vector<vector<int>> &rectangles) 
    {
        // Project rectangles onto X-axis as intervals [x1, x2]
        vector<vector<int>> xAxis = extractXAxisRanges(rectangles);

        // Project rectangles onto Y-axis as intervals [y1, y2]
        vector<vector<int>> yAxis = extractYAxisRanges(rectangles);

        // Try placing a vertical cut (line parallel to Y-axis)
        bool canCutVertically = hasValidNonOverlappingCut(xAxis);

        // Try placing a horizontal cut (line parallel to X-axis)
        bool canCutHorizontally = hasValidNonOverlappingCut(yAxis);

        // If we can make a valid cut in either direction, return true
        return canCutVertically || canCutHorizontally;
    }
};

/*
Approach Summary:

1. For each rectangle, extract its horizontal (x1 to x2) and vertical (y1 to y2) coverage.
2. For X-axis:
   - Sort all [x1, x2] intervals.
   - Try to find a gap between intervals (i.e., x1 > previous x2).
   - A vertical line can pass through such a gap without touching rectangles.
3. Same logic for Y-axis to find a valid horizontal line.
4. Return true if either vertical or horizontal line exists that intersects at most one rectangle.

Time Complexity: O(n log n)
    - Due to sorting x and y intervals.

Space Complexity: O(n)
    - For storing x and y projections of rectangles.
*/
