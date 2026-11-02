// Approach 1 — Brute Force         (Sort + Merge)            , learn approach 2 after this
class SummaryRanges
{
    vector<int> nums;

public:
    SummaryRanges()
    {
    }

    void addNum(int value)
    {
        nums.push_back(value);
    }

    vector<vector<int>> getIntervals()
    {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int num : nums)
        {
            // Duplicate number.
            if (!ans.empty() && ans.back()[1] >= num)
                continue;

            // Consecutive number.
            if (!ans.empty() && ans.back()[1] + 1 == num)
                ans.back()[1] = num;
            else
                ans.push_back({num, num});
        }

        return ans;
    }
};

/*
Approach 1: Sort + Merge

1. Store all incoming numbers in a vector.
2. Whenever getIntervals() is called, sort the vector.
3. Traverse sorted numbers:
   - Skip duplicates.
   - Merge consecutive numbers into the current interval.
   - Otherwise, create a new interval.

Time Complexity:
   addNum: O(1)
   getIntervals: O(N log N)

Space Complexity: O(N)
*/

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


class SummaryRanges
{
    map<int, int> intervals;

public:
    SummaryRanges()
    {
    }

    void addNum(int value)
    {
        auto it = intervals.lower_bound(value);

        // Case 1: Already present in the next interval.
        if (it != intervals.end() && it->first == value)
            return;

        auto prev = intervals.end();

        // Find previous interval.
        if (it != intervals.begin())
        {
            prev = std::prev(it);

            // Case 2: Already present in previous interval.
            if (prev->second >= value)
                return;
        }

        bool mergeLeft = prev != intervals.end() &&
                         prev->second + 1 == value;

        bool mergeRight = it != intervals.end() &&
                          it->first == value + 1;

        // Case 3: Merge both intervals.
        if (mergeLeft && mergeRight)
        {
            prev->second = it->second;
            intervals.erase(it);
        }

        // Case 4: Merge with left interval.
        else if (mergeLeft)
        {
            prev->second = value;
        }

        // Case 5: Merge with right interval.
        else if (mergeRight)
        {
            int end = it->second;

            intervals.erase(it);
            intervals[value] = end;
        }

        // Case 6: Create a new interval.
        else
        {
            intervals[value] = value;
        }
    }

    vector<vector<int>> getIntervals()
    {
        vector<vector<int>> ans;

        for (auto& [start, end] : intervals)
            ans.push_back({start, end});

        return ans;
    }
};

/*
Approach 2: Ordered Map + Interval Merging

1. Maintain intervals in an ordered map.
   Key = Start, Value = End.

2. Find the next interval using lower_bound(value).
   Find the previous interval using prev(it).

3. Check six cases:
   - Already present in next interval.
   - Already present in previous interval.
   - Merge both intervals.
   - Merge with left interval.
   - Merge with right interval.
   - Create a new interval.

4. getIntervals():
   Traverse map and return all intervals.
   Map automatically maintains sorted order.

Time Complexity:
   addNum: O(log N)
   getIntervals: O(K)

Space Complexity: O(K)

K = Number of disjoint intervals
N = Number of distinct inserted numbers
*/
