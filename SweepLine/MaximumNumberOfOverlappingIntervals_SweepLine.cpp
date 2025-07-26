#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Pure Difference Array + Prefix Sum
==============================================
 Idea:
We use a simple difference array where we mark +1 at the interval start
and -1 at the interval end+1 (since the interval is inclusive).

Then, we compute prefix sums to determine the number of active intervals at each point.

 Only works when the range of time is small (e.g., max end ≤ 10^6)

 Time: O(N + T) where T = max time value
 Space: O(T)
*/
int maxOverlap_diffArray(vector<vector<int>> &intervals)
{
    int maxTime = 0;
    for (auto &iv : intervals)
        maxTime = max(maxTime, iv[1]);

    vector<int> diff(maxTime + 2, 0);

    for (auto &iv : intervals)
    {
        diff[iv[0]] += 1;
        diff[iv[1] + 1] -= 1;
    }

    int active = 0, maxOverlap = 0;
    for (int i = 0; i <= maxTime + 1; ++i)
    {
        active += diff[i];
        maxOverlap = max(maxOverlap, active);
    }

    return maxOverlap;
}

/*
Approach 2: Line Sweep using Sorted Vector of Events
====================================================
 Idea:
Treat all interval start and end+1 points as events. At start, we increment count.
At end+1, we decrement it (since intervals are inclusive). Sort these events by time.

This way, we simulate a sweep line and count how many intervals are active at any moment.

 Time: O(N log N)
 Space: O(N)
*/
int maxOverlap_eventVec(vector<vector<int>> &intervals)
{
    vector<pair<int, int>> events;

    for (auto &iv : intervals)
    {
        events.push_back({iv[0], +1});         // Start event
        events.push_back({iv[1] + 1, -1});      // End+1 event
    }

    sort(events.begin(), events.end());

    int active = 0, maxOverlap = 0;

    for (auto &[time, delta] : events)
    {
        active += delta;
        maxOverlap = max(maxOverlap, active);
    }

    return maxOverlap;
}

/*
Approach 3: Line Sweep using Ordered Map
========================================
 Idea:
Instead of sorting a vector of events, use a map to maintain all time points
and their cumulative deltas.

Map keys are automatically sorted, so we can perform the sweep line without explicit sorting.

 Time: O(N log N)
 Space: O(N)
*/
int maxOverlap_eventMap(vector<vector<int>> &intervals)
{
    map<int, int> timeChanges;

    for (auto &iv : intervals)
    {
        timeChanges[iv[0]] += 1;
        timeChanges[iv[1] + 1] -= 1;
    }

    int active = 0, maxOverlap = 0;
    for (auto &[time, delta] : timeChanges)
    {
        active += delta;
        maxOverlap = max(maxOverlap, active);
    }

    return maxOverlap;
}

// ===========================
// Main function to test above
// ===========================
int main()
{
    vector<vector<int>> intervals = {{1, 2}, {2, 4}, {3, 6}};

    cout << "Using Difference Array     : " << maxOverlap_diffArray(intervals) << endl;
    cout << "Using Event Vector (Sweep) : " << maxOverlap_eventVec(intervals) << endl;
    cout << "Using Event Map (Sweep)    : " << maxOverlap_eventMap(intervals) << endl;

    return 0;
}
