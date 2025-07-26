#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> employeeFreeTime(vector<vector<int>> &schedule)
    {
        map<int, int> timeline; // time → change in number of active workers

        // Step 1: Apply difference array logic on working intervals
        for (auto &interval : schedule)
        {
            int start = interval[0];
            int end = interval[1];

            timeline[start] += 1; // worker becomes active
            timeline[end] -= 1;   // worker becomes inactive (we use 'end' not 'end + 1' because interval is [start, end))
        }

        vector<vector<int>> freeTimes;
        int active = 0;
        int lastFreeStart = -1;

        // Step 2: Traverse the timeline in sorted order
        for (auto &[time, delta] : timeline)
        {
            active += delta;

            if (active == 0)
            {
                // All workers are inactive: free interval starts
                lastFreeStart = time;
            }
            else if (lastFreeStart != -1 && time > lastFreeStart)
            {
                // Work resumes: free interval ends
                freeTimes.push_back({lastFreeStart, time});
                lastFreeStart = -1; // reset for next possible free interval
            }
        }

        return freeTimes;
    }
};


/**
 Explanation:

We are given employee schedules with working intervals [start, end), and our goal is to find time ranges when no one is working.

 Steps:

 We use a difference array approach via a sorted map (sweep line):
    - At time `start`, one more person starts working → `+1`
    - At time `end`, that person stops working → `-1`
        -- We do NOT use `end + 1` because the problem clearly defines the interval as **half-open**: [start, end). 
           That means the person is **not working at time = end**, so we decrement at `end` itself.

 We simulate a sweep line over time:
    - Keep a count `active` of how many people are currently working.
    - When `active == 0`, no one is working → this is a potential start of a free time.
    - As soon as someone starts working again, we end the free time interval.

 This gives us a list of all common free times.

 Time Complexity: O(N log N)
- Sorting the time points via map traversal.

 Space Complexity: O(N)
- For the map and output result.


**/
