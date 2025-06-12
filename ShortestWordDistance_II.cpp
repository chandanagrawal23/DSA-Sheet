class WordDistance
{
private:
    // Maps each word to its list of indices
    unordered_map<string, vector<int>> locations; 

public:
    // Constructor to map each word to all its positions
    WordDistance(vector<string>& words)
    {
        for (int i = 0; i < words.size(); ++i)
        {
            locations[words[i]].push_back(i);
        }
    }

    // Returns the shortest distance between two words
    int shortest(string word1, string word2)
    {
        vector<int>& loc1 = locations[word1];
        vector<int>& loc2 = locations[word2];

        int i = 0, j = 0;
        int minDiff = INT_MAX;

        // Two pointer technique to find min absolute difference
        while (i < loc1.size() && j < loc2.size())
        {
            minDiff = min(minDiff, abs(loc1[i] - loc2[j]));

            if (loc1[i] < loc2[j])
                i++;
            else
                j++;
        }

        return minDiff;
    }
};

/*
Approach:
- Preprocess all words and map each word to a list of its indices.
- For query shortest(word1, word2), use two pointers to compare the sorted index lists and find the minimum absolute difference.

Time:
- Constructor: O(n), where n = number of words
- shortest(): O(L1 + L2), where L1 and L2 are number of occurrences of word1 and word2

Space: O(n), for storing word to index mapping
*/
