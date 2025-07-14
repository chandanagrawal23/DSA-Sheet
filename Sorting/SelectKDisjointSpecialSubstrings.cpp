class Solution
{
public:
    bool maxSubstringLength(string s, int k)
    {
        int n = s.size();
        vector<int> firstOccurrence(26, -1), lastOccurrence(26, -1);

        // Record the first and last occurrences of each character
        for (int i = 0; i < n; i++)
        {
            int chIndex = s[i] - 'a';
            if (firstOccurrence[chIndex] == -1)
            {
                firstOccurrence[chIndex] = i;
            }
            lastOccurrence[chIndex] = i;
        }

        vector<pair<int, int>> validIntervals;

        // Find valid intervals for characters
        for (int i = 0; i < n; i++)
        {
            int chIndex = s[i] - 'a';

            // Only check interval if this is the first occurrence
            if (i != firstOccurrence[chIndex])
            {
                continue;
            }

            int intervalEnd = lastOccurrence[chIndex];

            // Expand the interval to include all characters whose last occurrence
            // lies beyond the current interval
            for (int j = i; j <= intervalEnd; j++)
            {
                intervalEnd = max(intervalEnd, lastOccurrence[s[j] - 'a']);
            }

            // Validate the interval: no character should start before i
            bool isValid = true;
            for (int j = i; j <= intervalEnd; j++)
            {
                if (firstOccurrence[s[j] - 'a'] < i)
                {
                    isValid = false;
                    break;
                }
            }

            if (!isValid)
            {
                continue;
            }

            // Exclude whole string as one interval
            if (i == 0 && intervalEnd == n - 1)
            {
                continue;
            }

            validIntervals.push_back({i, intervalEnd});
        }

        // Sort intervals by end index to prepare for greedy selection
        sort(validIntervals.begin(), validIntervals.end(),
             [](const pair<int, int> &a, const pair<int, int> &b)
             {
                 return a.second < b.second;
             });

        // Greedily count non-overlapping intervals
        int count = 0, currentEnd = -1;
        for (const auto &interval : validIntervals)
        {
            if (interval.first > currentEnd)
            {
                count++;
                currentEnd = interval.second;
            }
        }

        return count >= k;
    }
};

/**
Approach:
Given a string `s`, the goal is to find at least `k` non-overlapping substrings such that:
- Each substring contains all occurrences of every character it includes.
- No substring is the entire string.

Steps:
1. Track the first and last occurrences of each character.
2. For each character's first occurrence, try to build the smallest valid interval `[i, end]`:
   - Expand the interval to include any character whose last occurrence lies beyond `end`.
   - Check that no character in this interval has a first occurrence before `i`.
3. Skip intervals that span the entire string.
4. Use greedy strategy to select the maximum number of **non-overlapping** intervals:
   - Sort intervals by end time.
   - Always pick the next interval that starts after the current one ends.

Edge Cases:
- Entire string is not allowed as a valid interval.
- Duplicates and overlapping intervals are pruned carefully.

Time Complexity:
- O(N) to collect first/last occurrences.
- O(N^2) worst-case for validating and expanding intervals.
- O(N log N) for sorting valid intervals.
- O(N) for greedy selection.

Space Complexity:
- O(N) for storing intervals and occurrence arrays.
*/
