class Solution
{
public:
    string alienOrder(vector<string>& words)
    {
        unordered_map<char, unordered_set<char>> graph; // adjacency list
        unordered_map<char, int> indegree;              // incoming edge count

        // Step 1: Initialize all characters
        for (const string& word : words)
        {
            for (char c : word)
            {
                graph[c];       // ensure node exists
                indegree[c] = 0;
            }
        }

        // Step 2: Build graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++)
        {
            string& w1 = words[i];
            string& w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool foundEdge = false;

            for (int j = 0; j < len; j++)
            {
                if (w1[j] != w2[j])
                {
                    // Add edge w1[j] -> w2[j] if not already added
                    if (graph[w1[j]].insert(w2[j]).second)
                    {
                        indegree[w2[j]]++;
                    }
                    foundEdge = true;
                    break;
                }
            }

            // Edge case: invalid input like ["abc", "ab"]
            if (!foundEdge && w1.size() > w2.size())
                return "";
        }

        // Step 3: Topological sort (Kahn's algorithm)
        queue<char> q;
        for (auto& [ch, deg] : indegree)
        {
            if (deg == 0)
                q.push(ch);
        }

        string result;
        while (!q.empty())
        {
            char curr = q.front(); q.pop();
            result += curr;

            for (char neighbor : graph[curr])
            {
                if (--indegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        // If result doesn't contain all characters → cycle detected
        return result.size() == indegree.size() ? result : "";
    }
};

/*
🧠 Detailed Approach:

1️⃣ Build a directed graph:
   - For each pair of adjacent words, compare character by character.
   - First differing character tells you the precedence rule: a → b.
   - Add this as an edge in the graph and increase indegree of b.

2️⃣ Handle invalid case:
   - If word1 is longer than word2 and word2 is a prefix of word1 → return "".

3️⃣ Perform Topological Sort (Kahn's Algorithm):
   - Start with characters with indegree 0.
   - Repeatedly remove from queue and reduce indegree of neighbors.
   - Track the result order.

4️⃣ Detect cycles:
   - If the result string contains fewer characters than total unique characters → cycle → return "".

⏱️ Time Complexity: O(N * L)
   - N = number of words, L = average word length (for pairwise comparison)

📦 Space Complexity: O(1)
   - Maximum of 26 lowercase English letters

✅ Returns one valid character ordering consistent with the alien dictionary.
*/
