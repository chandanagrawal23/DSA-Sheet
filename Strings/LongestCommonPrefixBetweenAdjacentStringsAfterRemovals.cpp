class Solution 
{
public:
    // helper to compute LCP length of two strings
    int lcpLen(string& a, string& b) 
    {
        int i = 0, j = 0, len = 0;
        while (i < a.size() && j < b.size() && a[i] == b[j]) 
        {
            len++;
            i++;
            j++;
        }
        return len;
    }

    vector<int> longestCommonPrefix(vector<string>& words)
    {
        int n = words.size();

        // lcpPref[i] = max LCP among pairs in [0..i]
        vector<int> lcpPref(n, 0);

        // lcpSuff[i] = max LCP among pairs in [i..n-1]
        vector<int> lcpSuff(n, 0);

        // build prefix max LCP array
        for (int i = 1; i < n; i++) 
        {
            lcpPref[i] = max(lcpPref[i - 1], lcpLen(words[i - 1], words[i]));
        }

        // build suffix max LCP array
        for (int i = n - 2; i >= 0; i--) 
        {
            lcpSuff[i] = max(lcpSuff[i + 1], lcpLen(words[i], words[i + 1]));
        }

        vector<int> ans(n, 0);

        // compute answer for each removal
        for (int i = 0; i < n; i++) 
        {
            // left side pairs
            if (i - 1 >= 0)
                ans[i] = lcpPref[i - 1];

            // right side pairs
            if (i + 1 < n)
                ans[i] = max(ans[i], lcpSuff[i + 1]);

            // new pair formed between (i-1, i+1)
            if (i - 1 >= 0 && i + 1 < n) 
                ans[i] = max(ans[i], lcpLen(words[i - 1], words[i + 1]));
        }

        return ans;
    }
};

/**
 Approach:
 - For each index i, we need the maximum LCP among adjacent pairs after removing words[i].
 - Precompute two helper arrays:
   1. lcpPref[i] = max LCP among pairs in [0..i].
   2. lcpSuff[i] = max LCP among pairs in [i..n-1].
 - When removing words[i]:
   - Left contribution = lcpPref[i-1].
   - Right contribution = lcpSuff[i+1].
   - New pair contribution = LCP(words[i-1], words[i+1]).
 - Take the maximum of these to form ans[i].

 Time Complexity:
 - O(total characters) to compute all adjacent LCPs once
 - O(n) for prefix + suffix + answer loop
 - Overall: O(n + total chars), where sum of word lengths ≤ 1e5.

 Space Complexity:
 - O(n) for prefix, suffix, and answer arrays
 - O(1) extra apart from input
*/
