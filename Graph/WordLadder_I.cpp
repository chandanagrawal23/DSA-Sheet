class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end())
        {
            return 0; // End word must exist in dictionary
        }

        unordered_set<string> visited;
        queue<string> q;
        q.push(beginWord);
        visited.insert(beginWord);
        int steps = 1;

        while (!q.empty())
        {
            int levelSize = q.size();
            while (levelSize--)
            {
                string word = q.front();
                q.pop();

                if (word == endWord)
                {
                    return steps;
                }

                // Try all one-letter transformations
                for (int i = 0; i < word.size(); ++i)
                {
                    char originalChar = word[i];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        if (c == originalChar)
                            continue;

                        word[i] = c;
                        // if newly formed word is present in wordSet and not visited yet
                        if (wordSet.count(word) && !visited.count(word))
                        {
                            visited.insert(word);
                            q.push(word);
                        }
                    }
                    word[i] = originalChar; // Restore original character
                }
            }

            steps++; // Move to next transformation level
        }

        return 0; // No valid transformation sequence
    }
};

/*
Approach:
- Perform BFS from the `beginWord`, transforming one character at a time.
- Only valid transformations (i.e., words present in the `wordList`) are enqueued.
- Use a `visited` set to avoid revisiting words.
- BFS guarantees that the first time we reach `endWord`, it is through the shortest transformation sequence.

Time Complexity: O(N * L * 26)
- N: number of words in wordList
- L: average word length
- 26: possible characters to try at each position

Space Complexity: O(N * L)
- For the word set, visited set, and queue.
*/
