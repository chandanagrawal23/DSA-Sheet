#include <bits/stdc++.h>
using namespace std;

class MyCalendarThree
{
    map<int, int> timelineChanges; // time -> net change (+1 for start, -1 for end)
    int maxConcurrent = 0;         // Maximum overlapping events at any point

public:
    MyCalendarThree() {}

    int book(int startTime, int endTime)
    {
        // Mark the start of an event (+1 at startTime)
        timelineChanges[startTime] += 1;

        // Mark the end of an event (-1 at endTime)
        //  Why not endTime + 1? ,  Because the interval is [startTime, endTime) → half-open
        // So we remove at 'end', not end + 1
        timelineChanges[endTime] -= 1;

        int ongoing = 0;
        maxConcurrent = 0;

        // Traverse timeline in order to calculate max overlap
        for (auto &[time, delta] : timelineChanges)
        {
            ongoing += delta;                // Apply changes at current time
            maxConcurrent = max(maxConcurrent, ongoing);
        }

        return maxConcurrent;
    }
};

/*
 Approach (Line Sweep / Difference Map):
-----------------------------------------
Each booking [startTime, endTime) is a half-open interval:
→ +1 at startTime means a new event starts
→ -1 at endTime means that event ends *before* endTime

We store these changes in a map<int, int>, which automatically keeps keys sorted.
Then, simulate from left to right (like prefix sum) to compute current active events.

For each booking, we scan the timeline and update the maximum number of simultaneous events seen so far.

$$ Note: We use `endTime` directly (not endTime+1) because the interval is half-open.

 Time Complexity:
- book() call takes O(N log N), where N is the number of unique time points.
- Since at most 400 calls are made, this is efficient enough.

 Space Complexity: O(N) — for the timeline map
*/

