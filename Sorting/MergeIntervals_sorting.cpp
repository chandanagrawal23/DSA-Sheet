class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        // Sort intervals by their starting time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;

        for (auto interval : intervals) 
        {
            // If merged is empty or current interval does not overlap, add it directly
            if (merged.empty() || merged.back()[1] < interval[0])
            {
                merged.push_back(interval);
            }
            // Else merge with the last interval by extending its end time
            else
            {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }

        return merged;
    }
};

/**
Approach:
1. First, we sort the intervals based on their starting times.
   This ensures that any overlapping intervals will be adjacent in the sorted order.

2. We then iterate over the sorted intervals:
   - If the current interval does not overlap with the last merged interval 
     (i.e., current.start > merged.back().end), we add it as a new interval.
   - If there is an overlap (i.e., current.start <= merged.back().end), 
     we merge them by updating the end of the last merged interval to 
     the maximum of current.end and merged.back().end.

3. This guarantees that all overlapping intervals are merged into one 
   and non-overlapping ones are preserved.

Time Complexity:
- O(N log N) due to sorting.
- O(N) for the merge loop.

Space Complexity:
- O(N) for the output list of merged intervals.
*/
