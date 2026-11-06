// Approach 1 : Trie + Vector + Sorting (Simpler) , Brute Force

class AutocompleteSystem
{
    struct Node
    {
        Node* child[27]{};
        vector<string> sentences; // All sentences having this prefix
    };

    Node* root;
    Node* curr;

    string currentInput;
    unordered_map<string, int> freq;

    int getIndex(char ch)
    {
        return ch == ' ' ? 26 : ch - 'a';
    }

    void insert(string& s)
    {
        Node* node = root;

        for (char ch : s)
        {
            int idx = getIndex(ch);

            if (!node->child[idx])
                node->child[idx] = new Node();

            node = node->child[idx];

            node->sentences.push_back(s);
        }
    }

    vector<string> getTop3(Node* node)
    {
        if (!node)
            return {};

        auto candidates = node->sentences;

        // Sort by frequency descending, then lexicographically
        sort(candidates.begin(), candidates.end(),
             [&](const string& a, const string& b)
             {
                 if (freq[a] != freq[b])
                     return freq[a] > freq[b];

                 return a < b;
             });

        if (candidates.size() > 3)
            candidates.resize(3);

        return candidates;
    }

public:

    AutocompleteSystem(vector<string>& sentences,
                       vector<int>& times)
    {
        root = new Node();
        curr = root;

        for (int i = 0; i < sentences.size(); i++)
            freq[sentences[i]] = times[i];

        for (auto& s : sentences)
            insert(s);
    }

    vector<string> input(char c)
    {
        if (c == '#')
        {
            freq[currentInput]++;

            // Insert only if this is a completely new sentence
            if (freq[currentInput] == 1)
                insert(currentInput);

            currentInput.clear();
            curr = root;

            return {};
        }

        currentInput += c;

        if (curr)
            curr = curr->child[getIndex(c)];

        return getTop3(curr);
    }
};

/*

Approach
1. Build a Trie where every node stores a vector of all sentences matching its prefix.
2. Maintain sentence frequencies in an unordered_map.
3. When a character arrives, move to the corresponding Trie node.
4. Copy all candidate sentences from that node.
5. Sort candidates using:
   - Higher frequency first.
   - Lexicographically smaller sentence first when frequencies are equal.
6. Return the first three sentences.
7. When # arrives, increment the sentence frequency. If it is a new sentence, insert it into the Trie.
Complexity

Let:
- L = length of the sentence.
- K = number of sentences sharing the current prefix.
Operation	Complexity
Initialization	(O(sum L_i))
Input character	(O(K log K))
Update existing sentence	(O(1))
Insert new sentence	(O(L))
Space	(O(sum L_i cdot N)) upper bound


*/

/* ====================================================================================================================================================== */

// Approach 2 : Trie + Set (Optimized)
class AutocompleteSystem
{
    struct Node
    {
        Node* child[27]{};
        set<pair<int, string>> hot; // Stores sentences in ranking order
    };

    Node* root;
    Node* curr;

    string currentInput;
    unordered_map<string, int> freq;

    int getIndex(char ch)
    {
        return ch == ' ' ? 26 : ch - 'a';
    }

    void update(string& s, int delta)
    {
        int oldFreq = freq[s];
        int newFreq = oldFreq + delta;

        freq[s] = newFreq;

        Node* node = root;

        for (char ch : s)
        {
            int idx = getIndex(ch);

            if (!node->child[idx])
                node->child[idx] = new Node();

            node = node->child[idx];

            // Remove old ranking before inserting updated ranking
            if (oldFreq > 0)
                node->hot.erase({-oldFreq, s});

            node->hot.insert({-newFreq, s});
        }
    }

public:

    AutocompleteSystem(vector<string>& sentences,
                       vector<int>& times)
    {
        root = new Node();
        curr = root;

        currentInput = "";

        for (int i = 0; i < sentences.size(); i++)
            update(sentences[i], times[i]);
    }

    vector<string> input(char c)
    {
        if (c == '#')
        {
            update(currentInput, 1);

            currentInput.clear();
            curr = root;

            return {};
        }

        currentInput += c;

        if (curr)
            curr = curr->child[getIndex(c)];

        vector<string> ans;

        if (!curr)
            return ans;

        int count = 0;

        // Set already maintains the required ranking
        for (auto& p : curr->hot)
        {
            if (count == 3)
                break;

            ans.push_back(p.second);
            count++;
        }

        return ans;
    }
};

/*

Approach
1. Build a Trie where each node represents a prefix.
2. Every Trie node maintains a set<pair<int,string>> containing all sentences having that prefix.
3. Store frequency as negative frequency (-freq) so that higher frequency comes first in ascending set order.
4. If frequencies are equal, lexicographically smaller strings come first.
5. When a sentence is entered using #, update its frequency in the map and update its ranking in every Trie node along its path.
6. For every character, move to the corresponding Trie node and return the first three sentences from its set.
Complexity

Let:
- L = length of the sentence.
- K = number of sentences sharing a prefix.
Operation	Complexity
Initialization	(O(sum L_i log N))
Input character	(O(1)) Trie traversal + (O(3)) retrieval
Update sentence	(O(L log N))
Space	(O(sum L_i cdot N)) upper bound

*/
