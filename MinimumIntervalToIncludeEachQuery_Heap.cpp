#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> minInterval(vector<vector<int>> &intervals, vector<int> &queries)
    {
        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // Pair each query with its index
        vector<pair<int, int>> q;
        for (int i = 0; i < queries.size(); i++)
        {
            q.push_back({queries[i], i});
        }
        sort(q.begin(), q.end()); // Sort queries by value

        // Min-heap: {interval size, interval end}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

        vector<int> ans(queries.size(), -1);
        int i = 0; // pointer for intervals

        for (auto &[query, idx] : q)
        {
            // Add all intervals whose start ≤ query
            while (i < intervals.size() && intervals[i][0] <= query)
            {
                int start = intervals[i][0], end = intervals[i][1];
                int size = end - start + 1;
                minHeap.push({size, end});
                i++;
            }

            // Remove all intervals that end < query
            while (!minHeap.empty() && minHeap.top().second < query)
            {
                minHeap.pop();
            }

            // Top of heap is the smallest valid interval
            if (!minHeap.empty())
            {
                ans[idx] = minHeap.top().first;
            }
        }

        return ans;
    }
};

/*
 Approach: Sorting + Min-Heap

1. Sort all intervals by their start value.
2. Sort all queries, while keeping their original index.
3. For each query in sorted order:
   - Add all intervals starting ≤ query into a min-heap (by size).
   - Remove intervals whose end < query (they cannot contain it).
   - The top of the heap now contains the smallest valid interval containing the query.
4. Restore the original order of queries using stored indices.

 Time Complexity:
- Sorting Intervals: O(N log N)
- Sorting Queries: O(Q log Q)
- Each interval added & removed once from heap: O(N log N)
- Each query: O(log N) for heap
→ Total: O((N + Q) log N)

 Space Complexity:
- O(N + Q) for heap, queries, and result
*/
