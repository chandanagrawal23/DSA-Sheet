
class Solution
{
    struct Node
    {
        Node* child[26]{};
        int count = 0;
    };

    void insert(Node* root, string& s)
    {
        Node* curr = root;

        for (char ch : s)
        {
            int idx = ch - 'a';

            if (!curr->child[idx])
                curr->child[idx] = new Node();

            curr = curr->child[idx];
            curr->count++;
        }
    }

    int getPrefix(Node* root, string& s)
    {
        Node* curr = root;

        for (int i = 0; i < s.size(); i++)
        {
            curr = curr->child[s[i] - 'a'];

            // Stop when the prefix becomes unique.
            if (curr->count == 1)
                return i + 1;
        }

        return s.size();
    }

    string makeAbbr(string& s, int len)
    {
        int middle = s.size() - len - 1;

        string abbr = s.substr(0, len) + to_string(middle) + s.back();

        return abbr.size() < s.size() ? abbr : s;
    }

public:
    vector<string> wordsAbbreviation(vector<string>& words)
    {
        int n = words.size();
        vector<string> ans(n);

        // Step 1: Group by initial abbreviation.
        unordered_map<string, vector<int>> groups;

        for (int i = 0; i < n; i++)
        {
            string abbr = makeAbbr(words[i], 1);
            groups[abbr].push_back(i);
        }

        // Step 2: Process each group, because only words in the same group can collide.
        // Example: [interval, internal] => [i6l, i6l]

        for (auto& [abbr, ids] : groups)
        {
            // Already unique.
            if (ids.size() == 1)
            {
                ans[ids[0]] = abbr;
                continue;
            }

            // Step 3: Build Trie for the collision group.
            Node* root = new Node();

            for (int id : ids)
                insert(root, words[id]);

            // Step 4: Find the shortest unique prefix.
            // Traverse the Trie until prefix count becomes 1.
            // This is similar to LPM (Longest Prefix Matching) traversal.
            for (int id : ids)
            {
                int len = getPrefix(root, words[id]);
                ans[id] = makeAbbr(words[id], len);
            }
        }

        return ans;
    }
};

/*
Approach: Grouping + Trie (Shortest Unique Prefix)

1. Group by Initial Abbreviation:
   Words having the same initial abbreviation are grouped together.
   Only these words can create abbreviation collisions.

2. Build Trie:
   Build a separate Trie for each collision group.
   Each node maintains the count of words passing through it.

3. Find Unique Prefix:
   Traverse the Trie until count == 1.
   This gives the shortest prefix that uniquely identifies the word.

4. Generate Abbreviation:
   Prefix + Number of omitted characters + Last character.
   If abbreviation length >= original word length, return original word.

Time Complexity: O(N * L)
Space Complexity: O(N * L)

N = Number of words
L = Maximum length of a word
*/
