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
