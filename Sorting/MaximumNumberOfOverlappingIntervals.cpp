/////////////////////////////////////////////////////
// 1. Brute Force Approach
/////////////////////////////////////////////////////
class BruteForceSolution
{
public:
    int maxOverlap(vector<vector<int>> &intervals)
    {
        int minTime = INT_MAX, maxTime = INT_MIN;
        for (auto &interval : intervals)
        {
            minTime = min(minTime, interval[0]);
            maxTime = max(maxTime, interval[1]);
        }

        int maxOverlap = 0;

        for (int time = minTime; time <= maxTime; time++)
        {
            int currentOverlap = 0;
            for (auto &interval : intervals)
            {
                if (interval[0] <= time && time < interval[1])
                {
                    currentOverlap++;
                }
            }
            maxOverlap = max(maxOverlap, currentOverlap);
        }

        return maxOverlap;
    }
};

/*
Approach:
Iterate over all possible time points between the earliest start and latest end.
For each time, count how many intervals it lies within.
Keep track of the maximum count.

Time: O(N^2) in worst case
Space: O(1)
*/

/////////////////////////////////////////////////////
// 2. Min Heap Approach
/////////////////////////////////////////////////////
class MinHeapSolution
{
public:
    int maxOverlap(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end()); // sort by start time

        priority_queue<int, vector<int>, greater<int>> activeEnds;
        int maxOverlap = 0;

        for (auto &interval : intervals)
        {
            int start = interval[0];
            int end = interval[1];

            // Remove intervals that ended before current start
            while (!activeEnds.empty() && activeEnds.top() <= start)
            {
                activeEnds.pop();
            }

            activeEnds.push(end);
            maxOverlap = max(maxOverlap, (int)activeEnds.size());
        }

        return maxOverlap;
    }
};

/*
Approach:
Sort intervals by start time. Use a min-heap to track ongoing intervals.
Remove all intervals from the heap that have already ended before current start.
Push current interval's end. Heap size tells active overlaps.

Time: O(N log N)
Space: O(N)
*/

/////////////////////////////////////////////////////
// 3. Line Sweep Approach
/////////////////////////////////////////////////////
class LineSweepSolution
{
public:
    static bool compareEvents(const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.first != b.first)
        {
            return a.first < b.first;
        }
        return a.second > b.second; // +1 before -1 at same time
    }

    int maxOverlap(vector<vector<int>> &intervals)
    {
        vector<pair<int, int>> events;

        for (auto &interval : intervals)
        {
            events.push_back({interval[0], +1}); // start event
            events.push_back({interval[1], -1}); // end event
        }

        sort(events.begin(), events.end(), compareEvents);

        int currentOverlap = 0, maxOverlap = 0;
        for (auto &event : events)
        {
            currentOverlap += event.second;
            maxOverlap = max(maxOverlap, currentOverlap);
        }

        return maxOverlap;
    }
};

/*
Approach:
Convert each interval to a start (+1) and end (-1) event.
Sort events: by time, and prefer start over end if same time.
Do prefix sum on sorted events to find peak overlap.

Time: O(N log N)
Space: O(N)
*/

/////////////////////////////////////////////////////
// 4. Two Pointer Style
/////////////////////////////////////////////////////
class TwoPointerSolution
{
public:
    int maxOverlap(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        vector<int> startTimes, endTimes;

        for (auto &interval : intervals)
        {
            startTimes.push_back(interval[0]);
            endTimes.push_back(interval[1]);
        }

        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());

        int i = 0, j = 0;
        int currentOverlap = 0, maxOverlap = 0;

        while (i < n)
        {
            if (startTimes[i] < endTimes[j])
            {
                currentOverlap++;
                maxOverlap = max(maxOverlap, currentOverlap);
                i++;
            }
            else
            {
                currentOverlap--;
                j++;
            }
        }

        return maxOverlap;
    }
};

/*
Approach:
Split start and end times into two arrays and sort them.
Use two pointers to simulate arrivals and departures.
Increase overlap on arrival, decrease on departure. Track max.

Time: O(N log N)
Space: O(N)
*/


/*

✅ Summary Table
Approach	            Time Complexity	             Space Complexity	               Notes
Brute Force	             O(N²)	                        O(1)	             Slowest, good for understanding
Min Heap	               O(N log N)	                    O(N)	             Greedy, keeps ongoing intervals
Line Sweep	             O(N log N)                    	O(N)	             Most elegant and efficient
Two Pointer	             O(N log N)	                    O(N)	             Variation of line sweep

*/
