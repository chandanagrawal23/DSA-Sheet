/////////////////////////////////////////////////////
// Find Right Interval Using Map + Binary Search
/////////////////////////////////////////////////////
class Solution
{
public:
    vector<int> findRightInterval(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        vector<int> result(n);
        map<int, int> startIndexMap; // {start time -> original index}

        // Map each start time to its index
        for (int i = 0; i < n; ++i)
        {
            startIndexMap[intervals[i][0]] = i;
        }

        // For each interval, find the smallest start >= current end
        for (int i = 0; i < n; ++i)
        {
            auto it = startIndexMap.lower_bound(intervals[i][1]);

            // store index if found, else -1
            if(it != startIndexMap.end())
            {
                result[i] = it->second;
            }
            else
            {
                result[i] = -1;
            }
        }

        return result;
    }
};


/**
Approach:
We need to find for each interval the index of the interval whose start time is the smallest
but greater than or equal to its end time.

Steps:
1. Use a map to store all (start time -> original index), map auto-sorts by key.
2. For each interval, use lower_bound on map to get the smallest start >= end.
3. If such a start exists, use the corresponding index; otherwise, return -1.

Time Complexity: O(N log N)
- O(N log N) to build the map
- O(N log N) for N lower_bound queries

Space Complexity: O(N)
*/

/////////////////////////////////////////////////////
// Find Right Interval Using Custom Binary Search
/////////////////////////////////////////////////////
class Solution
{
public:
    // Binary search for smallest start >= target
    int findSmallestStart(vector<pair<int, int>> &startIndexPairs, int targetEnd)
    {
        int left = 0, right = startIndexPairs.size() - 1;
        int resultIndex = -1;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (startIndexPairs[mid].first >= targetEnd)
            {
                resultIndex = startIndexPairs[mid].second;
                right = mid - 1; // try for smaller start
            }
            else
            {
                left = mid + 1;
            }
        }

        return resultIndex;
    }

    vector<int> findRightInterval(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        vector<pair<int, int>> sortedStarts; // {start, original index}

        for (int i = 0; i < n; ++i)
        {
            sortedStarts.push_back({intervals[i][0], i});
        }

        sort(sortedStarts.begin(), sortedStarts.end());

        vector<int> result(n);
        for (int i = 0; i < n; ++i)
        {
            int endTime = intervals[i][1];
            result[i] = findSmallestStart(sortedStarts, endTime);
        }

        return result;
    }
};

/**
Approach:
We want to find for each interval the index of the interval whose start is >= the current interval's end.

Steps:
1. Pair all start times with their original index.
2. Sort these pairs by start time.
3. For each interval, do a binary search on the sorted list to find the smallest start >= current end.
4. If found, use the stored index, else store -1.

Time Complexity:
- O(N log N) for sorting
- O(N log N) for binary search per interval

Space Complexity:
- O(N) for storing start times and result
*/
