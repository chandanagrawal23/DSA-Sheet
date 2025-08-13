class Solution
{
public:
    // Checks if src can be stretched to match dst
    bool isExpressive(const string &dst, const string &src)
    {
        int i = 0, j = 0;
        int n = dst.size(), m = src.size();

        while (i < n && j < m)
        {
            // Characters must match
            if (dst[i] != src[j])
                return false;

            int dstCount = 1;
            int srcCount = 1;

            // Count consecutive same chars in dst
            while (i + 1 < n && dst[i] == dst[i + 1])
            {
                i++;
                dstCount++;
            }

            // Count consecutive same chars in src
            while (j + 1 < m && src[j] == src[j + 1])
            {
                j++;
                srcCount++;
            }

            // Stretching rule check:
            // - If counts match, fine
            // - If counts differ, dst group must be >= 3
            //   and word group must be <= dst group
            if (dstCount != srcCount and (srcCount > dstCount || dstCount < 3))
            {
                return false;
            }

            // Move to next group
            i++;
            j++;
        }

        // Both strings must be fully processed
        return i == n && j == m;
    }

    int expressiveWords(string target, vector<string> &words)
    {
        int count = 0;

        for (const auto &w : words)
        {
            if (isExpressive(target, w))
            {
                count++;
                // cout << w << " ";
            }
        }
        return count;
    }
};

/**
Approach:
---------
1. For each word, we check if it can be stretched to match the target string.
2. We scan both strings in parallel, grouping consecutive identical characters.
3. Let `dstCount` be the size of a group in target, and `srcCount` for the word.
4. Stretching rules:
   - If counts match → OK
   - If counts differ → dstCount must be >= 3 and dstCount >= srcCount
5. If all groups satisfy rules and both strings end together, it's expressive.

Time Complexity:
----------------
- Let L = length of target, W = average length of a word, K = number of words.
- `isExpressive` runs in O(L + W) for each word.
- Total = O(K * (L + W)).

Space Complexity:
-----------------
- O(1) extra space (only counters and pointers).
*/
