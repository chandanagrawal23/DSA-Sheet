class Solution
{
public:
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2)
    {
        int minDistance = INT_MAX;  // Store the shortest distance
        int previousIndex = -1;     // Last seen index of word1 or word2

        for (int i = 0; i < wordsDict.size(); ++i)
        {
            string &currentWord = wordsDict[i];

            // Check if current word matches either word1 or word2
            if (currentWord == word1 || currentWord == word2)
            {
                // Check for valid previous occurrence:
                // - Either it's a different word than current
                // - Or both words are the same
                if (previousIndex != -1)
                {
                    if((wordsDict[previousIndex] != currentWord) || (word1 == word2))
                    {
                        minDistance = min(minDistance, i - previousIndex);
                    }
                }
                
                // Update previous index
                previousIndex = i;
            }
        }

        return minDistance;
    }
};

/*
Approach:
- Traverse the array and track the last seen index of word1 or word2.
- If a valid pair is found (different words or same word at different locations), compute distance.
- Update the minimum distance accordingly.

Time: O(n), where n = number of words in wordsDict
Space: O(1), only constant extra space used
*/
