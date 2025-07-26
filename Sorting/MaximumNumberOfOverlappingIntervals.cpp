/////////////////////////////////////////////////////
/*
1. Brute Force Approach
Approach:
Iterate over all possible time points between the earliest start and latest end.
For each time, count how many intervals it lies within.
Keep track of the maximum count.

Time: O(N^2) in worst case
Space: O(1)
*/
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

/////////////////////////////////////////////////////
// 2. Min Heap Approach
/*
Approach:
Sort intervals by start time. Use a min-heap to track ongoing intervals.
Remove all intervals from the heap that have already ended before current start.
Push current interval's end. Heap size tells active overlaps.

Time: O(N log N)
Space: O(N)
*/
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

