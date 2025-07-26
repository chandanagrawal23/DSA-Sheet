
#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> componentSize;
    int totalComponents;

    DSU(int n) {
        parent.resize(n);
        componentSize.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
        totalComponents = n;
    }

    int find(int node) {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV)
            return false;
        if (componentSize[rootU] >= componentSize[rootV]) {
            parent[rootV] = rootU;
            componentSize[rootU] += componentSize[rootV];
        } else {
            parent[rootU] = rootV;
            componentSize[rootV] += componentSize[rootU];
        }
        totalComponents--;
        return true;
    }

    bool sameComponent(int u, int v) {
        return find(u) == find(v);
    }

    int getSize(int u) {
        return componentSize[find(u)];
    }

    int getComponentCount() {
        return totalComponents;
    }
};

class Solution {
public:
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        // Step 1: Map words to indices
        unordered_map<string, int> wordToIndex;
        int index = 0;
        for (const auto& pair : synonyms) {
            if (!wordToIndex.count(pair[0]))
                wordToIndex[pair[0]] = index++;
            if (!wordToIndex.count(pair[1]))
                wordToIndex[pair[1]] = index++;
        }

        // Step 2: Initialize DSU
        int sz = wordToIndex.size();
        DSU dsu(sz);
        for (const auto& pair : synonyms) {
            int u = wordToIndex[pair[0]];
            int v = wordToIndex[pair[1]];
            dsu.unite(u, v);
        }

        // Step 3: Group words by component
        unordered_map<int, vector<string>> components;
        for (const auto& [word, idx] : wordToIndex) {
            int root = dsu.find(idx);
            components[root].push_back(word);
        }
        // Sort words in each component lexicographically
        for (auto& [root, words] : components) {
            sort(words.begin(), words.end());
        }

        // Step 4: Split text into words
        vector<string> sentence;
        stringstream ss(text);
        string word;
        while (ss >> word) {
            sentence.push_back(word);
        }

        // Step 5: DFS to generate sentences
        vector<string> result;
        vector<string> current;
        dfs(0, sentence, wordToIndex, components, current, result);

        // Step 6: Sort result lexicographically
        sort(result.begin(), result.end());
        return result;
    }

private:
    void dfs(int pos, const vector<string>& sentence,
             unordered_map<string, int>& wordToIndex, // Removed const
             unordered_map<int, vector<string>>& components, // Removed const
             vector<string>& current, vector<string>& result) {
        // Base case: reached end of sentence
        if (pos >= sentence.size()) {
            result.push_back(join(current, " "));
            return;
        }

        // Current word
        string word = sentence[pos];
        // If word is not in synonyms, use it as is
        if (!wordToIndex.count(word)) {
            current.push_back(word);
            dfs(pos + 1, sentence, wordToIndex, components, current, result);
            current.pop_back();
        } else {
            // Try each synonym in the word's component
            int root = wordToIndex[word]; // Use operator[]
            for (const string& synonym : components[root]) { // Use operator[]
                current.push_back(synonym);
                dfs(pos + 1, sentence, wordToIndex, components, current, result);
                current.pop_back();
            }
        }
    }

    // Helper function to join words with a delimiter
    string join(const vector<string>& words, const string& delim) {
        string result;
        for (size_t i = 0; i < words.size(); ++i) {
            result += words[i];
            if (i < words.size() - 1) result += delim;
        }
        return result;
    }
};

int main() {
    Solution solution;

    // Example 1
    cout << "Example 1:\n";
    vector<vector<string>> synonyms1 = {{"happy", "joy"}, {"sad", "sorrow"}, {"joy", "cheerful"}};
    string text1 = "I am happy today but was sad yesterday";
    vector<string> result1 = solution.generateSentences(synonyms1, text1);
    cout << "Output: [\n";
    for (const string& sentence : result1) {
        cout << "  \"" << sentence << "\"" << (sentence == result1.back() ? "\n" : ",\n");
    }
    cout << "]\n\n";

    // Example 2
    cout << "Example 2:\n";
    vector<vector<string>> synonyms2 = {{"happy", "joy"}, {"cheerful", "glad"}};
    string text2 = "I am happy today but was sad yesterday";
    vector<string> result2 = solution.generateSentences(synonyms2, text2);
    cout << "Output: [\n";
    for (const string& sentence : result2) {
        cout << "  \"" << sentence << "\"" << (sentence == result2.back() ? "\n" : ",\n");
    }
    cout << "]\n";

    return 0;
}
/*
Approach:

1. Map Words to Indices: Assign a unique index to each word in the synonyms list using an unordered_map (wordToIndex). This allows efficient lookup and DSU operations.
2. Initialize DSU: Create a Disjoint Set Union (DSU) structure with size equal to the number of unique words. Unite each synonym pair’s indices to group synonymous words into connected components.
3. Group Words by Component: Use DSU to find the root of each word’s index and group words by their root in a map (components). Sort each component’s words lexicographically.
4. Split Text: Split the input text into a vector of words using stringstream.
5. DFS to Generate Sentences: Use Depth-First Search to generate all possible sentences:
   - For each word position, if the word has no synonyms, use it as is.
   - If it has synonyms, try each word in its DSU component, recursively building sentences.
   - When all words are processed, join the current sentence with spaces and add to the result.
6. Sort Result: Sort the generated sentences lexicographically before returning.


Time Complexity: O(M * α(M) + N * 2^K * L + K * log K)
- M: Number of unique words in synonyms (≤ 2 * synonyms.length ≤ 20).
- α(M): Inverse Ackermann function for DSU operations (nearly constant).
- N: Number of words in the sentence (≤ 10).
- K: Number of sentence words with synonyms (≤ N).
- L: Average length of a sentence string.
- DSU setup and operations: O(M * α(M)) for uniting synonym pairs and finding roots.
- Component sorting: O(M * log M) for sorting words in components (each component has ≤ M words).
- Text splitting: O(N * L) for parsing the sentence.
- DFS: O(2^K * N * L), where 2^K is the number of possible sentences (each of K words can have multiple synonyms), and N * L is the cost of building each sentence.
- Result sorting: O(K * log K * L), where K is the number of sentences (≤ 2^K), and L is the average sentence length for string comparisons.
- Given small constraints, the dominant term is O(2^K * N * L), but K ≤ 10 makes this feasible.

Space Complexity: O(M + N + 2^K * N * L)
- M: Space for wordToIndex and components maps (O(M)).
- N: Space for sentence vector and DFS recursion stack (O(N)).
- 2^K * N * L: Space for the result vector, as there can be up to 2^K sentences, each of length O(N * L).
- DSU arrays: O(M) for parent and componentSize.
- The output dominates if many sentences are generated, but constraints keep it manageable.

*/
