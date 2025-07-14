class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
        {
            return 0;
        }

        int num_removed = 0;

        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // Start with the end of the first interval
        int currEnd = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            // If there is overlap
            if (intervals[i][0] < currEnd)
            {
                num_removed++;

                // Keep the interval that ends earlier to minimize future overlap
                currEnd = min(currEnd, intervals[i][1]);
            }
            else
            {
                // No overlap, update current end to this interval's end
                currEnd = intervals[i][1];
            }
        }

        return num_removed;
    }
};

/**
Approach:
We want to remove the "minimum number of overlapping intervals" from a list to make the rest non-overlapping.

1. First, we sort the intervals by their start time.
2. We iterate over the sorted list and compare the current interval with the previously chosen non-overlapping interval.
   - If they "overlap" (i.e., current start < previous end), we "remove one".
     To make a greedy decision, we keep the one that ends "earlier" so that it has "less chance to overlap" with upcoming intervals.
   - If they don’t overlap, we move forward and update the currEnd.

This is a classic greedy strategy where we try to "remove the interval" that could cause more future overlaps.

Time Complexity:
- O(N log N) due to sorting.

Space Complexity:
- O(1) extra space (in-place).

Note:
To avoid overlap, always choose the interval with the earliest end time among overlapping options.
*/
