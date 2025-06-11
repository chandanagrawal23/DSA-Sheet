class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) 
    {
        if (intervals.empty())
            return 0;

        // sort intervals with startTime first and then endTime
        // so that we will process whose meeting is scheduled early
        sort(intervals.begin(), intervals.end());

        // min heap which stores the end time of each interval
        priority_queue<int, vector<int>, greater<>> pq;

        // push first interval's end time
        pq.push(intervals[0][1]);

        for (int i = 1; i < intervals.size(); i++)
        {
            int lastEndTime = pq.top();
            int currentStartTime = intervals[i][0];
            int currentEndTime  = intervals[i][1];

            // if the end time of last meeting is less means it ended already before current meeting
            // then we can remove the last meeting
            if (lastEndTime <= currentStartTime)
            {
                pq.pop();
            }

            // push the ending time of current meeting
            pq.push(currentEndTime);
        }
        
        // The size of the heap tells us the minimum rooms required for all the meetings
        return pq.size();
    }
};

// Approach:
// Sort the meetings by start time.
// Use a min-heap to track the end time of ongoing meetings.
// For each meeting, if its start time is after the earliest ending meeting, reuse that room (pop the heap).
// Otherwise, a new room is needed (push into the heap).
// The size of the heap at the end gives the minimum number of rooms required.

// Time Complexity: O(n log n)
// - Sorting takes O(n log n)
// - Each push/pop operation in the heap takes O(log n), and we do this n times in the worst case.

// Space Complexity: O(n)
// - In the worst case, all meetings overlap, so the heap will contain all n meeting end times.
