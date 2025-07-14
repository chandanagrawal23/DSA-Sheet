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
