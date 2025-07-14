// Approach 1 :
class Solution
{
public:
    int removeCoveredIntervals(vector<vector<int>> &intervals)
    {
        // Sort by start ascending, and end ascending by default
        sort(intervals.begin(), intervals.end());

        int prevStart = intervals[0][0];
        int prevEnd = intervals[0][1];

        int remainingCount = 1; // First interval is always included

        for (int i = 1; i < intervals.size(); ++i)
        {
            int currStart = intervals[i][0];
            int currEnd = intervals[i][1];

            // If the current interval is not fully covered by the previous one
            if (currStart > prevStart && currEnd > prevEnd)
            {
                remainingCount++;
            }

            // Update the reference interval to the one with farther reach
            if (currEnd > prevEnd)
            {
                prevStart = currStart;
                prevEnd = currEnd;
            }
        }

        return remainingCount;
    }
};

/**
Approach:
We want to count how many intervals are *not* fully covered by any previous interval.

Steps:
1. Sort the intervals by start time. If start times are equal, smaller end comes first.
2. Initialize `prevStart` and `prevEnd` as the start and end of the first interval.
3. Traverse each interval:
   - If it starts after `prevStart` and ends after `prevEnd`, it is not covered.
   - Increment the count for such intervals.
   - Regardless of coverage, update `prevStart` and `prevEnd` if this interval ends later.

Why it works:
- Sorting ensures that potential covering intervals appear before the ones they might cover.
- The check `(start > prevStart && end > prevEnd)` ensures full containment is ruled out.

Time Complexity:
- O(N log N) for sorting.
- O(N) for the scan.

Space Complexity:
- O(1) extra space.




1.The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
	eg Interval [3,6] is covered by [2,8], therefore it should be removed.
	
	Let see the Number line :)
	
	                                           1  2  3  4  5  6  7  8
											   1-------4
											         3--------6
												  2-----------------8
	clearly we can see that [3 6] is covered by [2,8] and therefore it should be removed.

2. We will Sort the vector in ascending order to get this type of arrangement.
		//e.g. (1,5), (1,8), (2,9), (3,5), (4,7), (4,9)
		
3. For finding the remaining interaval, ifa[1][0] && a[1][1] both greater than a[0][0] && a[0][1],
this means the previous interval is not covered by the next one, therefore we will increase the count.
			consider the case [[1,3],[2,4],[4,8]]
								1   2  3  4  5  6  7  8
								1------3
									2-----4
									      4-----------8
											 
No interval is completely overlaped by other therefore remainig interaval are 3.

how answer is 3 , at first cnt is initialised to 1
now a[0,0] i.e 1 and a[1,0] i.e 2   1 < 2 also,
    a[0,1] i.e 3 and a[1,1] i.e 4   3 < 4    , therefore cnt is incremented by 2 now,
		
		also a[2,0] and a[2,1] satisy same condition with a[1,0] and a[1,1] , cnt becomes 3
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Approach 2

class Solution
{
public:
    static bool compare(const vector<int> &a, const vector<int> &b)
    {
        // Sort by start ascending.
        // If starts are equal, sort by end descending to keep larger range first.
        if (a[0] != b[0])
        {
            return a[0] < b[0];
        }
        return a[1] > b[1];
    }

    int removeCoveredIntervals(vector<vector<int>> &intervals)
    {
        // Sort using the custom comparator
        sort(intervals.begin(), intervals.end(), compare);

        int covered_intervals = 0;
        int maximum_end = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            // If current interval is completely covered by previous
            if (intervals[i][1] <= maximum_end)
            {
                covered_intervals++;
            }
            else
            {
                // Update max end since this one is not covered
                maximum_end = intervals[i][1];
            }
        }

        // Return the number of non-covered intervals
        return intervals.size() - covered_intervals;
    }
};

/**
Approach:
We are given a list of intervals, and we want to remove all intervals that are completely covered by another.

Steps:
1. Sort the intervals:
   - By start point in ascending order.
   - If start points are equal, sort by end point in descending order.
     This ensures that a larger interval comes before the one it might cover.

2. Initialize `maximum_end` as the end of the first interval.
3. Traverse the rest of the intervals:
   - If `interval[i].end <= maximum_end`, it is covered — increment count.
   - Otherwise, update `maximum_end` to the new interval’s end.

4. Return `total_intervals - covered_intervals`.

Why this works:
- Sorting ensures that any interval which can potentially cover another is before it in the list.
- The check `end <= maximum_end` confirms full coverage.

Time Complexity:
- O(N log N) for sorting.
- O(N) for single pass to count covered intervals.

Space Complexity:
- O(1) extra space (in-place).
*/

