class Solution
{
public:
    int maxSubstrings(string word)
    {
        int totalSubstrings = 0;            // Count of valid substrings
        vector<int> firstOccurrence(26, -1); // To store first index of each character
        int n = word.length();

        for (int i = 0; i < n; i++)
        {
            int charIndex = word[i] - 'a';

            // If this character was seen earlier in this block
            // and substring length is at least 4
            if (firstOccurrence[charIndex] != -1 && i - firstOccurrence[charIndex] + 1 >= 4)
            {
                totalSubstrings++;               // Found a valid substring

                // Reset all entries to -1 to start a new non-overlapping block
                for (int j = 0; j < 26; j++)
                    firstOccurrence[j] = -1;
            }
            else
            {
                // First time seeing this character in current block
                if (firstOccurrence[charIndex] == -1)
                    firstOccurrence[charIndex] = i;
            }
        }

        return totalSubstrings;
    }
};

/*
Approach:

- We are asked to find the maximum number of **non-overlapping** substrings
  that are at least 4 characters long and start and end with the same letter.

- To solve this, we scan the string from left to right and track the first index
  where each character appears (using a 26-element array `firstOccurrence`).

- When we revisit a character and the length of substring between first occurrence
  and current index is at least 4, we count it as a valid substring.

- To maintain the non-overlapping condition, we **reset** the firstOccurrence array
  after each valid substring is counted.

- This greedy approach works because we always take the first valid opportunity
  to select a valid substring, ensuring future ones do not intersect with it.

Time Complexity: O(N * 26) — each time we find a valid substring, we reset 26 entries.
Space Complexity: O(26) — constant space to track first occurrences of characters.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// there will be a high possibility u think like merge interval, now worries below code helps you 
class Solution {
public:
    // Custom lower_bound to find the first index where arr[i] >= val
    int customLowerBound(const vector<int>& arr, int startIdx, int val) 
    {
        int low = startIdx, high = arr.size() - 1, ans = arr.size();
        while (low <= high) 
        {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= val) 
            {
                ans = mid;
                high = mid - 1;
            } 
            else 
            {
                low = mid + 1;
            }
        }
        return ans;
    }

    int maxSubstrings(string word) 
    {
        int n = word.size();
        vector<vector<int>> charIndices(26);

        // Step 1: Store all indices for each character
        for (int i = 0; i < n; ++i) 
        {
            charIndices[word[i] - 'a'].push_back(i);
        }

        vector<pair<int, int>> intervals;

        // Step 2: For each character, generate valid intervals
        for (int ch = 0; ch < 26; ++ch) 
        {
            const auto& idxs = charIndices[ch];
            for (int i = 0; i < idxs.size(); ++i) 
            {
                int start = idxs[i];
                // Find the first index >= start + 3 to ensure length >= 4
                int pos = customLowerBound(idxs, i + 1, start + 3);
                if (pos < idxs.size()) 
                {
                    intervals.emplace_back(idxs[pos], start);
                }
            }
        }

        // Step 3: Sort by end and greedily select non-overlapping intervals
        sort(intervals.begin(), intervals.end());

        int count = 0, lastEnd = -1;
        for (auto& [end, start] : intervals) 
        {
            if (start > lastEnd) 
            {
                count++;
                lastEnd = end;
            }
        }

        return count;
    }
};
/*
Approach:

1. For each character from 'a' to 'z', we store all indices at which it appears in the string.
2. For each index `i` of a character, we find the first later index `j` such that:
     - the substring from i to j is of length at least 4
     - word[i] == word[j] (same character)
   This ensures a valid substring that starts and ends with the same letter and has length >= 4.
   We use binary search (`customLowerBound`) to find `j` efficiently.
3. For each such valid pair (i, j), we store it as an interval [start = i, end = j].
4. We sort all such intervals by their end positions.
5. Now, using a greedy approach (like activity selection), we select non-overlapping intervals.
   - We always pick the earliest ending interval that doesn’t overlap with previously picked ones.

This way, we ensure:
- All substrings are non-overlapping.
- Each one satisfies the length and start-end character condition.
- We maximize the number of such substrings.

Time Complexity:
- O(N + 26 * logN) for collecting character positions and binary searching
- O(K log K) for sorting K intervals (K ≤ N)
- O(K) for greedy selection
⇒ Overall: O(N log N)

Space Complexity:
- O(N) to store character indices and intervals
*/
