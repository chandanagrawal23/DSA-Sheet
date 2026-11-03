class Solution {
public:
    string alienOrder(vector<string>& words) {

        vector<vector<int>> adj(26);
        vector<int> indegree(26, 0);
        vector<bool> present(26, false);

        // Mark characters that actually exist
        for (string& word : words) 
        {
            for (char c : word) 
            {
                present[c - 'a'] = true;
            }
        }

        // Build graph using adjacent words
        for (int i = 0; i + 1 < words.size(); i++) 
        {

            string& a = words[i];
            string& b = words[i + 1];

            int len = min(a.size(), b.size());
            int j = 0;

            // Find first different character
            while (j < len && a[j] == b[j])
                j++;

            // Invalid prefix case
            if (j == len && a.size() > b.size())
                return "";

            // First different characters give ordering aage ka need nhi
            // kyuki jab ye char hi nhi mila to aage to ham nhi bol skte relative ordering
            if (j < len) 
            {
                int u = a[j] - 'a';
                int v = b[j] - 'a';

                adj[u].push_back(v);
                indegree[v]++;
            }
        }

        queue<int> q;

        for (int i = 0; i < 26; i++) 
        {
            if (present[i] && indegree[i] == 0)
                q.push(i);
        }

        string ans;

        while (!q.empty()) 
        {

            int cur = q.front();
            q.pop();

            ans += char('a' + cur);

            for (int next : adj[cur]) 
            {

                indegree[next]--;

                if (indegree[next] == 0)
                    q.push(next);
            }
        }


        int totalChars = 0;

        for (bool x : present)
            totalChars += x;
            
        // Cycle detected
        if (ans.size() != totalChars)
            return "";

        return ans;
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
