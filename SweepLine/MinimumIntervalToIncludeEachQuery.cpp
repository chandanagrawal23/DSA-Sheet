#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> minInterval(vector<vector<int>> &intervals, vector<int> &queries)
    {
        vector<tuple<int, int, int>> events;

        // Step 1: Add interval start and end+1 as events
        for (auto &iv : intervals)
        {
            int l = iv[0], r = iv[1];
            int size = r - l + 1;
            events.push_back({l, 0, size});     // type 0: add interval
            events.push_back({r + 1, 1, size}); // type 1: remove interval at r + 1
        }

        // Step 2: Add queries as events with type 2
        for (int i = 0; i < queries.size(); ++i)
        {
            events.push_back({queries[i], 2, i}); // type 2: query
        }

        // Step 3: Sort by position, then type
        sort(events.begin(), events.end());

        multiset<int> activeSizes;              // Store active interval sizes
        vector<int> res(queries.size(), -1);    // Final answers

        // Step 4: Line sweep through events
        for (auto &[time, type, val] : events)
        {
            if (type == 0)
            {
                // Add interval size
                activeSizes.insert(val);
            }
            else if (type == 1)
            {
                // Remove interval size
                activeSizes.erase(activeSizes.find(val));
            }
            else
            {
                // Process query
                if (!activeSizes.empty())
                {
                    res[val] = *activeSizes.begin(); // Minimum interval covering this query
                }
            }
        }

        return res;
    }
};

/*
Approach: Line Sweep (using r+1 for removal)

We convert each interval into two events:
- One when it **starts** at `l` → we `add` its size
- One when it **ends** at `r+1` → we `remove` its size

We also convert each query into an event.

 Event Structure: {position, type, value}
- type = 0 → add interval size
- type = 1 → remove interval size (at r+1, so interval includes r)
- type = 2 → query event

We sort all events by:
1. Position
2. Then by type (0 < 1 < 2) so:
   - We **add** intervals before removing or querying
   - **Remove** comes before **query**, so at time r+1 the interval is gone

 Data Structure:
- We use a multiset to store all currently active intervals (by size)
- The answer to a query is the smallest value in the multiset

 Time Complexity: O((N + Q) * log(N + Q))
- Each event insert/erase in multiset is log N

 Space Complexity: O(N + Q)
- For storing events and multiset

*/
