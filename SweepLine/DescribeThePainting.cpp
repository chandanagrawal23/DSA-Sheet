// sweep Line
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments)
    {
        map<int, long long> colorChange;  // position → change in color sum (difference array but here map)

        // Step 1: Populate the difference map
        for (auto& seg : segments)
        {
            int start = seg[0];
            int end = seg[1];
            int color = seg[2];

            colorChange[start] += color;    // Start adding color from 'start'

            // Subtract color at 'end' directly, because the segment is half-open: [start, end)
            // Color ends exactly at 'end' since [start, end) is half-open
            // So we remove color at 'end', not end + 1
            colorChange[end] -= color;
        }

        vector<vector<long long>> result;
        long long currentColorSum = 0;
        int prevPos = 0;

        // Step 2: Process the map in sorted order
        for (auto& [currPos, delta] : colorChange)
        {
            if (currentColorSum > 0)
            {
                // We had some active color between prevPos and currPos (half-open interval)
                result.push_back({(1ll*prevPos),(1ll*currPos),currentColorSum});
            }
            currentColorSum += delta;
            prevPos = currPos;
        }

        return result;
    }
};


/*
 Approach: Difference Array + Prefix Sum

1. Each segment is given as [start, end) with a color.
    - We want to simulate coloring this interval efficiently.
    - So we use the "difference array" trick via a map:
        - colorChange[start] += color
        - colorChange[end] -= color

    ## Why NOT use `end + 1`?
        → Because segments are "half-open": [start, end)
        → Add -c at 'end' (not end+1) because 'end' marks where the color stops in a half-open interval.

2️. The map keeps all event points sorted.
    - We simulate a sweep-line traversal and maintain `currentColorSum`.

3️. Between two change points (`prevPos` and `currPos`), if the color sum > 0,
    it means that interval was painted and we include it in the result.

* Time Complexity: O(N log N)
    (because of sorting keys in map while traversing)

* Space Complexity: O(N)
    (map stores at most 2 entries per segment — start and end)
*/
