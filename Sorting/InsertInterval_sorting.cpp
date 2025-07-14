class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size(), i = 0;
        vector<vector<int>> ans;

        // Case 1: Add all intervals that end before newInterval starts
        while (i < n && intervals[i][1] < newInterval[0])
        {
            ans.push_back(intervals[i]);
            i++;
        }

        // Case 2: Merge all overlapping intervals with newInterval
        while (i < n && intervals[i][0] <= newInterval[1])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]); // update start
            newInterval[1] = max(newInterval[1], intervals[i][1]); // update end
            i++;
        }
        ans.push_back(newInterval); // push the merged interval

        // Case 3: Add all intervals that come after the newInterval
        while (i < n)
        {
            ans.push_back(intervals[i]);
            i++;
        }

        return ans;
    }
};

/**
Approach:
We are given a list of non-overlapping, sorted intervals and a new interval to insert.

1. Traverse the original list and divide the work into 3 distinct cases:

   Case 1: Intervals that end before the new interval starts.
   - These do not overlap and are added directly to the result.

   Case 2: Intervals that overlap with the new interval.
   - We update the `newInterval` to merge overlapping ranges by taking the min of start 
     and max of end between newInterval and current interval.

   Case 3: Intervals that start after the newInterval ends.
   - These are also added directly to the result as they do not overlap.

2. By maintaining order and handling overlaps in one pass, we get the final result in O(N) time.

Time Complexity:
- O(N), where N is the number of intervals.

Space Complexity:
- O(N), for the output vector (ignoring in-place optimization).
*/
