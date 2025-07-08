// DP ( N^2 * K ) give TLE , but learn this first 
// ========================================================

#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution
{
public:
    vector<vector<int>> dp;

    int maxValue(vector<vector<int>>& events, int k)
    {
        int n = events.size();
        dp.assign(k + 1, vector<int>(n, -1));
        
        // Sort events based on start time
        sort(events.begin(), events.end());
        
        return dfs(0, 0, -1, events, k);
    }

    int dfs(int curIndex, int count, int prevEndTime, vector<vector<int>>& events, int k)
    {
        if (curIndex == events.size() || count == k)
            return 0;

        if (prevEndTime >= events[curIndex][0])
            return dfs(curIndex + 1, count, prevEndTime, events, k);

        if (dp[count][curIndex] != -1)
            return dp[count][curIndex];

        // Option 1: Skip current event
        int skip = dfs(curIndex + 1, count, prevEndTime, events, k);

        // Option 2: Take current event
        int take = events[curIndex][2] + dfs(curIndex + 1, count + 1, events[curIndex][1], events, k);

        return dp[count][curIndex] = max(skip, take);
    }
};

/*
Approach:
---------
- Sort the events by start time.
- Use DFS + Memoization (Top-Down DP).
- At each step, either:
   1. Skip the current event
   2. Take the current event if it doesn't overlap with the previous
- Recursively move to the next index, updating:
   - count of events taken
   - latest ending time
- Memoize using dp[count][curIndex] to avoid recomputation.

Time Complexity: O(n × n × k)
Space Complexity: O(n × k) for memo table + recursion stack

*/
// ==================================================================================================================================================

// this is AC code earilier we use simply DP which is giving TLE for 2 Tc's
class Solution
{
public:
    vector<vector<int>> dp;

    int maxValue(vector<vector<int>>& events, int k)
    {
        int n = events.size();
        dp.assign(n + 1, vector<int>(k + 1, -1));

        // Sort events by start time
        sort(events.begin(), events.end());

        return recur(0, k, events);
    }

    int recur(int i, int k, vector<vector<int>>& events)
    {
        if (i >= events.size() || k == 0)
            return 0;

        if (dp[i][k] != -1)
            return dp[i][k];

        // Option 1: Skip current event
        int skip = recur(i + 1, k, events);

        // Option 2: Take current event
        int nextIndex = findNext(events, events[i][1]);  // find next event starting after current ends
        int take = events[i][2] + recur(nextIndex, k - 1, events);

        return dp[i][k] = max(skip, take);
    }

    int findNext(vector<vector<int>>& events, int endTime)
    {
        int low = 0, high = events.size(), ans = events.size();

        // Binary search for next event with startTime > endTime
        while (low < high)
        {
            int mid = (low + high) / 2;
            if (events[mid][0] > endTime)
            {
                ans = mid;
                high = mid;
            }
            else
            {
                low = mid + 1;
            }
        }

        return ans;
    }
};

/*
Approach:
---------
- Sort the events by start time.
- Use DP to compute the max value from index i with k events remaining.
- For each event, choose to:
    (1) Skip it, or 
    (2) Take it, and jump to the next non-overlapping event (using binary search).
- Memoize results with dp[i][k] to avoid recomputation.

Time Complexity: O(n * k * log n)

O(n log n) for sorting + O(n * k * log n) for recursion with binary search.

Bhai kya question the ye, previously DP se AC tha ab nhi
*/
