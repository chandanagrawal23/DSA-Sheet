/*
APPROACH 1: Simple Sweep Line Without Merging (Can TLE)
========================================================

Idea:
-----
Use a sweep line algorithm to count how many integers are covered at least once.
We add +1 at start and -1 at end+1 using a map. During count(), we walk through
the sorted keys and count how many points lie within active intervals.

Issue:
------
This approach doesn't merge intervals. It keeps growing the map and reprocesses all
events every time `count()` is called (if modified), which can lead to TLE.

Time Complexity:
----------------
add()   : O(log N)
count() : O(M), where M = number of unique points added via events

Space Complexity: O(M)

*/

class CountIntervals
{
    map<int, int> events; // sweep line events
    bool ready = false;   // flag to indicate if count has been computed
    int totalCount = 0;

public:
    void add(int left, int right)
    {
        events[left] += 1;
        events[right + 1] -= 1;
        ready = false;
    }

    int count()
    {
        if (ready)
            return totalCount; // avoid recomputing

        int active = 0;
        int prev = -1;
        totalCount = 0;

        for (auto &[x, delta] : events)
        {
            if (active > 0 && prev != -1)
            {
                totalCount += x - prev;
            }

            active += delta;
            prev = x;
        }

        ready = true;
        return totalCount;
    }
};
///////////////////////////////////////////////////////////////////////////
/*
APPROACH 2: Line Sweep With Merging the Interval
==================================================

Idea:
-----
Same as above, but after every update we merge overlapping/adjacent intervals.
We only recompute when modified (lazy recomputation) and we store only merged
intervals for efficient future operations.

Time Complexity:
----------------
add()   : O(log N)
count() : O(M), but only if recomputation needed (once per modification)

Space Complexity: O(M)

*/
class CountIntervals {
public:
    // Balanced BST to store event points: start -> +1, end+1 -> -1
    map<int, int> track;

    int total = 0;      // total number of integers covered in current merged intervals
    bool modified = false; // flag to denote whether new intervals were added

    CountIntervals() {}

    void add(int left, int right) {
        // Step 1: Mark sweep line events
        track[left]++;          // interval starts at 'left'
        track[right + 1]--;     // interval ends at 'right' (inclusive)

        // Step 2: Mark that intervals have been updated
        modified = true;
    }

    int count() {
        // Only recompute if intervals were modified
        if (modified) {
            total = 0;
            int active = 0;
            int start = -1;

            // New merged version of track
            map<int, int> mtrack;

            // Step 3: Perform sweep line over sorted keys
            for (auto& [pos, val] : track) {
                if (active == 0) {
                    start = pos;  // starting a new merged interval
                }

                active += val;

                if (active == 0) {
                    // ending a merged interval
                    total += pos - start; // count length of interval
                    mtrack[start]++;
                    mtrack[pos]--;
                }
            }

            // Update main track to only contain merged intervals
            track = mtrack;
            modified = false;
        }

        return total;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
APPROACH 3: Dynamic Interval Merging Using BST
===============================================

Idea:
-----
Maintain a BST of merged intervals (start → end).
When a new interval [L, R] comes in:
- Find all overlapping intervals.
- Merge all overlapping ones into one big [L, R].
- Update total by subtracting removed lengths and adding new merged length.

Time Complexity:
----------------
add()   : O(log N + K), where K = number of overlapping intervals
count() : O(1)

Space Complexity: O(N), where N is number of disjoint merged intervals

*/
#include <map>
using namespace std;

class CountIntervals {
    map<int, int> merged;  // stores merged intervals as {start → end}
    int total = 0;

public:
    CountIntervals() {
        total = 0;
    }

    void add(int left, int right) {
        auto it = merged.lower_bound(left);

        // Check if previous interval overlaps
        if (it != merged.begin()) {
            --it;
            if (it->second < left) ++it;  // move forward if no overlap
        }

        // Start merging overlapping intervals
        while (it != merged.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            total -= (it->second - it->first + 1); // remove overlapped count
            it = merged.erase(it);  // erase and move to next
        }

        // Insert merged interval
        merged[left] = right;
        total += (right - left + 1); // update total covered count
    }

    int count() {
        return total;
    }
};

