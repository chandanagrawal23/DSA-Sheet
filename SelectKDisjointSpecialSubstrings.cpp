class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        vector<int> firstOccurrence(26, -1), lastOccurrence(26, -1);

        // Record first and last occurrences of each character
        for (int i = 0; i < n; i++) {
            int chIndex = s[i] - 'a';
            if (firstOccurrence[chIndex] == -1)
                firstOccurrence[chIndex] = i;
            lastOccurrence[chIndex] = i;
        }

        vector<pair<int, int>> validIntervals;

        // Identify valid character intervals
        for (int i = 0; i < n; i++) {
            int chIndex = s[i] - 'a';
            if (i != firstOccurrence[chIndex])
                continue;

            int intervalEnd = lastOccurrence[chIndex];

            // extend this interval end as much as we can for the lastOcurrence of each char between i to lastOccurrence[chIndex]
            for (int j = i; j <= intervalEnd; j++)
            {
                intervalEnd = max(intervalEnd, lastOccurrence[s[j] - 'a']);
            }

            // Check if this interval is valid , valid means we will check whether there is 
            // an char from i to intervalEnd whose first occurence is before the i , that means we can't take this interval
            
            bool isValid = true;
            for (int j = i; j <= intervalEnd; j++) {
                if (firstOccurrence[s[j] - 'a'] < i) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) 
                continue;
            if (i == 0 && intervalEnd == n - 1) 
                continue; // Exclude whole string

            validIntervals.push_back({i, intervalEnd});
        }

        // Sort intervals based on end index
        sort(validIntervals.begin(), validIntervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        // Count non-overlapping intervals
        int count = 0, currentEnd = -1;
        for (const auto& interval : validIntervals) {
            if (interval.first > currentEnd) {
                count++;
                currentEnd = interval.second;
            }
        }

        return count >= k;
    }
};
