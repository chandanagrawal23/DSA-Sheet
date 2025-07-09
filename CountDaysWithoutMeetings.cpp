class Solution 
{
public:
    int countDays(int days, vector<vector<int>>& meetings) 
    {
        if (meetings.empty())
            return days;  // No meetings, all days are free

        vector<pair<int, int>> intervals;

        // Convert to interval pairs for easy handling
        for (const auto& meeting : meetings) 
        {
            intervals.push_back({meeting[0], meeting[1]});
        }

        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        int totalBusyDays = 0;
        int start = intervals[0].first;
        int end = intervals[0].second;

        // Merge overlapping intervals
        for (const auto& interval : intervals) 
        {
            if (interval.first <= end) 
            {
                // Extend current interval if overlapping
                end = max(end, interval.second);
            } 
            else 
            {
                // Add previous interval's days
                totalBusyDays += end - start + 1;
                // Start a new interval
                start = interval.first;
                end = interval.second;
            }
        }

        // Add the last interval's days
        totalBusyDays += end - start + 1;

        // Subtract busy days from total days to get free days
        return days - totalBusyDays;
    }
};

/*
Approach:

Convert each meeting to an interval [start, end].

Sort all intervals by their start time.

Merge overlapping intervals:

If the current interval overlaps with the previous, merge them.

Else, add the non-overlapping interval to the total busy days and reset.

After processing all intervals, compute the final merged busy days.

Subtract total busy days from the given number of days.

Time Complexity: O(N log N) due to sorting
Space Complexity: O(N) to store the intervals
*/

