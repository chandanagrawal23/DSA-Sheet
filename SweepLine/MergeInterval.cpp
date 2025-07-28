#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        const int MAX = 10001;
        vector<int> diff(MAX * 2 + 2, 0); // Double index space to distinguish adjacency

        // Build the difference array using doubled indices
        for (auto& it : intervals)
        {
            int start = it[0] * 2;
            int end = it[1] * 2;

            diff[start] += 1;
            diff[end + 1] -= 1;
        }

        // Compute prefix sum from the difference array
        vector<int> prefix(diff.size());
        prefix[0] = diff[0];
        for (int i = 1; i < diff.size(); ++i)
        {
            prefix[i] = prefix[i - 1] + diff[i];
        }

        // Traverse prefix sum to find merged intervals
        vector<vector<int>> merged;
        int start = -1;
        for (int i = 0; i < prefix.size(); ++i)
        {
            if (prefix[i] > 0 && start == -1)
            {
                start = i; // Start of new interval
            }
            else if (prefix[i] == 0 && start != -1)
            {
                merged.push_back({start / 2, (i) / 2});
                start = -1;
            }
        }

        return merged;
    }
};

/*
Explanation:
============
This solution merges overlapping intervals using the difference array + prefix sum approach,
but enhances it to avoid merging adjacent intervals by using doubled indexing.

Why Classic Difference Array Fails:
-----------------------------------
In the standard diff+prefix method, both overlapping and adjacent intervals result in continuous
prefix > 0, which merges them incorrectly. For example, [1,4] and [5,6] would merge into [1,6].
This is wrong because they are adjacent, not overlapping.

Fix Using Double Indexing:
--------------------------
By mapping each original number to 2*x (start) and 2*x+1 (end), we ensure that adjacent intervals
are separated by at least 2 indices in the diff array. This allows the prefix to drop to zero between
adjacent intervals and thus treats them as distinct.

Time Complexity:
----------------
O(N + M), where N is the size of diff[] (constant bounded by max range) and M is number of intervals.

Space Complexity:
-----------------
O(N), where N is size of diff[] and prefix[] arrays.


*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// using Map
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        map<int, int> events;

        // Step 1: Mark start and end events
        for (auto& interval : intervals) {
            events[interval[0]]++;  // Increment at start
            events[interval[1]]--;  // Decrement at end (inclusive handling)
        }

        vector<vector<int>> merged;
        int cnt = 0;
        int start = -1;

        // Step 2: Sweep line over sorted keys
        for (auto& [pos, delta] : events) {
            if (cnt == 0)
                start = pos;  // Start of a new merged interval

            cnt += delta;

            if (cnt == 0)
                merged.push_back({start, pos});  // End of current merged interval
        }

        return merged;
    }
};

/*
Explanation:
============
This solution uses a sweep line algorithm with a map to merge overlapping intervals efficiently.
Each interval [start, end] contributes:
- +1 at `start` to denote beginning of an interval
- -1 at `end` to denote the end of an interval

We avoid using (end + 1) to keep things inclusive, treating intervals exactly as defined.

The map (sorted by keys) acts as our timeline. As we iterate:
- When count goes from 0 → positive, we are entering a merged interval.
- When count drops back to 0, we are exiting a merged group of intervals.
We then push [start, pos] into the result.

This method naturally merges overlapping intervals but does NOT merge adjacent intervals
like [1,2] and [3,4], since there's a gap where count remains 0.

Example:
--------
Input:  [[1,3],[2,6],[8,10],[15,18]]
Events: 1:+1, 2:+1, 3:-1, 6:-1, 8:+1, 10:-1, 15:+1, 18:-1
Sweep:
- cnt becomes 1 at 1 → start = 1
- cnt becomes 2 at 2
- cnt becomes 1 at 3
- cnt becomes 0 at 6 → push [1,6]
- cnt becomes 1 at 8 → start = 8
- cnt becomes 0 at 10 → push [8,10]
- cnt becomes 1 at 15 → start = 15
- cnt becomes 0 at 18 → push [15,18]

Final merged: [[1,6],[8,10],[15,18]]

Time Complexity:
----------------
O(N log N): Inserting N intervals into a map takes log N per insertion.
O(N): To traverse all keys and construct merged result.

Space Complexity:
-----------------
O(N): For storing map entries and the final merged intervals.

This method is precise, efficient, and handles adjacent intervals correctly
without accidental merging.
*/
