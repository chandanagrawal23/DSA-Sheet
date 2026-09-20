/*
Approach 1 : Min Heap / Priority Queue

Idea:
Sort intervals by start time.

For every current interval [start, end]:
- Remove all previous intervals whose end < start.
  These intervals are completely finished and cannot intersect.
- All remaining intervals have end >= start,
  so they intersect with the current interval.
- pq.size() gives the number of intersecting previous intervals.
- Add current interval's end to the heap for future intervals.

Since intervals are closed:
[1, 2] and [2, 3] intersect.
Therefore, remove only end < start, not end <= start.

Time  : O(n log n)
Space : O(n)

*/

class Solution
{
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        sort(intervals.begin(), intervals.end());

        priority_queue<int, vector<int>, greater<int>> pq;

        long long ans = 0;

        for(auto& interval : intervals)
        {
            int start = interval[0];
            int end = interval[1];

            while(!pq.empty() && pq.top() < start)
            {
                pq.pop();
            }

            // Current interval kitne previous intervals
            // ke saath intersect kar raha hai
            ans += pq.size();

            // Current interval ko future intervals ke liye add karo
            pq.push(end);
        }

        return ans;
    }
};


/*
Approach 2 : Two Pointers

Idea:
Store all start times and end times separately
and sort both arrays.

For the current start s[current]:
- current = number of previous intervals.
- expired = number of previous intervals whose
            end < s[current].
- These expired intervals cannot intersect current.
- Therefore:

      intersecting = current - expired

We do not need to know which end belongs to which interval.
We only need the number of previous intervals that are still active.

Since intervals are closed:
[1, 2] and [2, 3] intersect.
Therefore, use end < start, not end <= start.

Time  : O(n log n)
Space : O(n)

*/
class Solution
{
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        int n = intervals.size();

        vector<int> s;
        vector<int> e;

        for(auto& interval : intervals)
        {
            s.push_back(interval[0]);
            e.push_back(interval[1]);
        }

        sort(s.begin(), s.end());
        sort(e.begin(), e.end());

        long long ans = 0;

        int expired = 0;

        for(int current = 0; current < n; current++)
        {
            // Jo intervals current start se pehle hi
            // completely end ho chuke hain
            while(expired < current && e[expired] < s[current])
            {
                expired++;
            }

            // current previous intervals hain
            // expired intervals overlap nahi karte
            // baaki sab overlap karte hain
            ans += current - expired;
        }

        return ans;
    }
};


/*
Approach 3 : Sweep Line / Events

Idea:
Convert every interval into two events:

    [start, +1] -> interval starts
    [end,   -1] -> interval ends

active = number of currently active intervals.

When a START event occurs:
- The new interval intersects every currently active interval.
- So add active to the answer.
- Then increase active.

When an END event occurs:
- The interval is no longer active.
- Decrease active.

Important:
Intervals are closed.

Example:
    [1, 2]
    [2, 3]

They intersect at 2.

Therefore, if START and END happen at the same position,
START must be processed before END.

Time  : O(n log n)
Space : O(n)

*/

class Solution
{
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        vector<pair<int, int>> events;

        for(auto& interval : intervals)
        {
            int start = interval[0];
            int end = interval[1];

            events.push_back({start, 1});
            events.push_back({end, -1});
        }

        sort(events.begin(), events.end(),
            [](const pair<int, int>& a,
               const pair<int, int>& b)
            {
                if(a.first != b.first)
                {
                    return a.first < b.first;
                }

                // Closed intervals:
                // START before END at same coordinate
                return a.second > b.second;
            });

        long long ans = 0;
        long long active = 0;

        for(auto& event : events)
        {
            if(event.second == 1)
            {
                // Current interval intersects
                // all currently active intervals
                ans += active;

                active++;
            }
            else
            {
                active--;
            }
        }

        return ans;
    }
};
