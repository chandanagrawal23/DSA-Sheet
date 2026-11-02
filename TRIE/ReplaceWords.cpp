// Approach 1: Prefix Generation + Trie Search -> Learn first and then must move to second approach
class TrieNode
{
public:
    bool isWord;
    vector<TrieNode*> child;

    TrieNode()
    {
        isWord = false;
        child.resize(26, nullptr);
    }
};

class Solution
{
public:
    void buildTrie(string& s, TrieNode* root)
    {
        TrieNode* p = root;

        for (char ch : s)
        {
            int idx = ch - 'a';

            if (!p->child[idx])
                p->child[idx] = new TrieNode();

            p = p->child[idx];
        }

        p->isWord = true;
    }

    bool search(string& s, TrieNode* root)
    {
        TrieNode* p = root;

        for (char ch : s)
        {
            int idx = ch - 'a';

            if (!p->child[idx])
                return false;

            p = p->child[idx];
        }

        return p->isWord;
    }

    vector<string> Split(string& s)
    {
        string temp = "";
        vector<string> ans;

        for (char ch : s)
        {
            if (ch != ' ')
                temp += ch;
            else
            {
                ans.push_back(temp);
                temp = "";
            }
        }

        ans.push_back(temp);
        return ans;
    }

    string replaceWords(vector<string>& dictionary, string& sentence)
    {
        TrieNode* root = new TrieNode();

        for (string word : dictionary)
            buildTrie(word, root);

        vector<string> words = Split(sentence);
        string ans = "";

        // Approach 1: Generate every prefix and search in Trie.
        for (string word : words)
        {
            string temp = "";
            bool flag = false;

            for (char ch : word)
            {
                temp += ch;

                // Check whether current prefix is a dictionary word.
                if (search(temp, root))
                {
                    ans += temp;
                    flag = true;
                    break;
                }
            }

            if (!flag)
                ans += word;

            ans += " ";
        }

        ans.pop_back(); // for last extra space
        return ans;
    }
};

/*
Approach 1: Prefix Generation + Trie Search

1. Build Trie using all dictionary words.
2. Split sentence into individual words.
3. For each word, generate prefixes one by one.
4. Search every prefix in Trie.
5. First matching prefix is the shortest root.
6. If no prefix matches, keep the original word.

Time Complexity:
   Trie Construction: O(D * L)
   Prefix Generation + Search: O(N * L^2)

   Total: O(D * L + N * L^2)

Space Complexity: O(D * L + N * L)

D = Number of dictionary words
N = Number of words in sentence
L = Maximum word length
*/

/* ===================================================================================================================================================================== */

// Approach 2 — Single Trie Traversal (Optimized)
class TrieNode
{
public:
    bool isWord;
    vector<TrieNode*> child;

    TrieNode()
    {
        isWord = false;
        child.resize(26, nullptr);
    }
};

class Solution
{
public:
    void buildTrie(string& s, TrieNode* root)
    {
        TrieNode* p = root;

        for (char ch : s)
        {
            int idx = ch - 'a';

            if (!p->child[idx])
                p->child[idx] = new TrieNode();

            p = p->child[idx];
        }

        p->isWord = true;
    }

    vector<string> Split(string& s)
    {
        string temp = "";
        vector<string> ans;

        for (char ch : s)
        {
            if (ch != ' ')
                temp += ch;
            else
            {
                ans.push_back(temp);
                temp = "";
            }
        }

        ans.push_back(temp);
        return ans;
    }

    string replaceWords(vector<string>& dictionary, string& sentence)
    {
        TrieNode* root = new TrieNode();

        for (string word : dictionary)
            buildTrie(word, root);

        vector<string> words = Split(sentence);
        string ans = "";

        // Approach 2: Find shortest root in a single Trie traversal.
        for (string word : words)
        {
            string temp = "";
            bool flag = false;
            TrieNode* p = root;

            for (char ch : word)
            {
                int idx = ch - 'a';

                // Prefix not found, so no root can match further.
                if (!p->child[idx])
                    break;

                p = p->child[idx];
                temp += ch;

                // Current prefix is a complete dictionary word.
                if (p->isWord)
                {
                    ans += temp;
                    flag = true;
                    break;
                }
            }

            if (!flag)
                ans += word;

            ans += " ";
        }

        ans.pop_back();
        return ans;
    }
};

/*
Approach 2: Single Trie Traversal

1. Build Trie using all dictionary words.
2. Split sentence into individual words.
3. For each word, traverse Trie character by character.
4. If a child is missing, stop traversal.
5. If isWord == true, shortest root is found.
6. If no root is found, keep the original word.

Time Complexity:
   Trie Construction: O(D * L)
   Sentence Traversal: O(N * L)

   Total: O(D * L + N * L)

Space Complexity: O(D * L + N * L)

D = Number of dictionary words
N = Number of words in sentence
L = Maximum word length
*/

// ----------------------------------------------------------------------------------------------

/*
Approach 1 mein agar word cattle hai, toh:
- c → Search
- ca → Search
- cat → Search
- catt → Search
Har search root se start hoti hai.

Approach 2 mein:
- c → Traverse
- ca → Traverse
- cat → isWord == true, stop!
Isliye Approach 2 mein repeated traversal eliminate ho jata hai.  
*/
