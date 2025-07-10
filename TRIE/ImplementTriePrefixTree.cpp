#include<bits/stdc++.h>
using namespace std;
class TrieNode
{
public:
    bool isWord;
    int countPrefix;
    vector<TrieNode*> children;
    TrieNode()
    {
        isWord = false;
        countPrefix = 0;
        children.resize(26, nullptr);
    }
};

class Trie
{
public:

    TrieNode* root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string& word)
    {
        TrieNode* node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (!node->children[idx])
            {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->countPrefix++;  // track number of words passing through
        }
        node->isWord = true;
    }

    bool search(const string& word)
    {
        TrieNode* node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (!node->children[idx])
            {
                return false;
            }
            node = node->children[idx];
        }
        return node->isWord;
    }

    bool startsWith(const string& prefix)
    {
        TrieNode* node = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (!node->children[idx])
            {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }

    int countWordsStartingWith(const string& prefix)
    {
        TrieNode* node = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (!node->children[idx])
            {
                return 0;
            }
            node = node->children[idx];
        }
        return node->countPrefix;
    }
};

// ✅ Now the Solution class uses the Trie
class Solution
{
private:
    Trie trie;

public:
    void addWord(const string& word)
    {
        trie.insert(word);
    }

    bool searchWord(const string& word)
    {
        return trie.search(word);
    }

    bool hasPrefix(const string& prefix)
    {
        return trie.startsWith(prefix);
    }

    int prefixCount(const string& prefix)
    {
        return trie.countWordsStartingWith(prefix);
    }
};

// ✅ Example usage
int main()
{
    Solution sol;

    sol.addWord("apple");
    sol.addWord("app");
    sol.addWord("april");
    sol.addWord("apron");

    cout << boolalpha;
    cout << "Search 'app': " << sol.searchWord("app") << "\n";             // true
    cout << "Search 'apps': " << sol.searchWord("apps") << "\n";           // false
    cout << "StartsWith 'apr': " << sol.hasPrefix("apr") << "\n";          // true
    cout << "Prefix count 'ap': " << sol.prefixCount("ap") << "\n";        // 4
    cout << "Prefix count 'apri': " << sol.prefixCount("apri") << "\n";    // 1

    return 0;
}
