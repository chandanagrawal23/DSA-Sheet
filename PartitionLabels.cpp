// Two approaches

// N + N
class Solution
{
public:
    vector<int> partitionLabels(string &S)
    {
        vector<int> lastCharIndex(26, 0); // Store the last index of each character (a-z)

        // Pass 1: Record the last occurrence of every character in the string
        for (int i = 0; i < S.size(); i++)
        {
            lastCharIndex[S[i] - 'a'] = i; // Update last seen index for current character
        }

        vector<int> results;              // To store sizes of each partition
        int maxLastCharIndex = -1;        // Max last index for characters in current window
        int lastStartIdx = 0;             // Start index of current partition

        // Pass 2: Traverse the string and create partitions
        for (int i = 0; i < S.size(); i++)
        {
            // Update the farthest last index we've seen for characters so far
            maxLastCharIndex = max(maxLastCharIndex, lastCharIndex[S[i] - 'a']);

            // If current index reaches the farthest last index, we found a partition
            if (i == maxLastCharIndex)
            {
                // Partition length = end - start + 1
                results.push_back(maxLastCharIndex - lastStartIdx + 1);

                // Move the start to next index for the upcoming partition
                lastStartIdx = i + 1;
            }
        }

        return results;
    }
};

/*
Approach:
- First, find the last index of each character.
- While traversing, keep track of the farthest last index for characters in the current window.
- When the current index matches the farthest last index, we know we can partition here.
- Push partition length and move to the next partition.

Time Complexity: O(N)   where N = length of string (2 passes over the string)
Space Complexity: O(1)  only 26 entries for lowercase alphabet
*/




// ========================================================================================================================================================

// same as Merge Interval 


class Solution
{
public:
    vector<int> partitionLabels(string &S)
    {
        int n = S.size();

        // Step 1: Store the first and last occurrence of each character
        vector<int> first(26, -1), last(26, -1);

        for (int i = 0; i < n; ++i)
        {
            int idx = S[i] - 'a';
            if (first[idx] == -1)
                first[idx] = i;
            last[idx] = i;
        }

        // Step 2: Collect all intervals
        vector<pair<int, int>> intervals;
        for (int i = 0; i < 26; ++i)
        {
            if (first[i] != -1)
                intervals.push_back({first[i], last[i]});
        }

        // Step 3: Sort intervals by start
        sort(intervals.begin(), intervals.end());

        // Step 4: Merge intervals
        vector<int> results;
        int prevStart = intervals[0].first, prevEnd = intervals[0].second;

        for (int i = 1; i < intervals.size(); ++i)
        {
            int currStart = intervals[i].first;
            int currEnd = intervals[i].second;

            if (currStart <= prevEnd)
            {
                prevEnd = max(prevEnd, currEnd); // merge
            }
            else
            {
                results.push_back(prevEnd - prevStart + 1); // push previous partition
                prevStart = currStart;
                prevEnd = currEnd;
            }
        }

        // Push the last merged interval
        results.push_back(prevEnd - prevStart + 1);

        return results;
    }
};

/*
Approach:
1. Store first and last occurrence of each character.
2. Treat each character's range [first, last] as an interval.
3. Sort the intervals by starting index.
4. Merge overlapping intervals and compute lengths of partitions.

Time Complexity: O(N + 26log26 + N) ≈ O(N) since max 26 intervals
Space Complexity: O(1) since character set is fixed (a-z)
*/

