// Brute force, just check except (from l to r) all characters are unique ?


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDeletion(string s)
    {
        int n = s.size();
        int ans = n;

        for(int l = 0; l <= n; l++)
        {
            for(int r = l; r <= n; r++)
            {
                vector<int> remainingChar(256, 0);
                bool valid = true;

                for(int i = 0; i < n; i++)
                {
                    if(i >= l && i < r)
                        continue;

                    unsigned char ch = s[i];

                    remainingChar[ch]++;

                    if(remainingChar[ch] > 1)
                    {
                        valid = false;
                        break;
                    }
                }

                if(valid)
                    ans = min(ans, r - l);
            }
        }

        return ans;
    }
};

/*
Approach:
1. Try every possible deletion [l, r).
2. Count frequencies of characters outside [l, r).
3. If all remaining characters are unique, update answer.
4. Return minimum deletion length.

Time: O(N^3)
Space: O(1) - fixed alphabet of 256 characters.
*/

// =====================================================================================================================================================================================

// Binary Search over answe , NlogN

#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool possible(string& s, int k)
    {
        int n = s.size();

        vector<int> remainingChar(256, 0);
        int duplicates = 0;

        // Initially delete [0, k)
        for(int i = k; i < n; i++)
        {
            unsigned char ch = s[i];

            remainingChar[ch]++;

            if(remainingChar[ch] == 2)
                duplicates++;
        }

        if(duplicates == 0)
            return true;

        // Slide deletion window
        for(int l = 0; l < n - k; l++)
        {
            // Add old deleted character
            unsigned char add = s[l];

            remainingChar[add]++;

            if(remainingChar[add] == 2)
                duplicates++;

            // Remove new deleted character
            unsigned char remove = s[l + k];

            if(remainingChar[remove] == 2)
                duplicates--;

            remainingChar[remove]--;

            if(duplicates == 0)
                return true;
        }

        return false;
    }

public:
    int minDeletion(string s)
    {
        int n = s.size();
        int low = 0, high = n;

        while(low < high)
        {
            int mid = low + (high - low) / 2;

            if(possible(s, mid))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};

/*
Approach:
1. Binary search on minimum deletion length k.
2. possible(k) checks if deleting exactly k consecutive
   characters can make the remaining string unique.
3. Initially delete [0, k) and count characters [k, n).
4. Slide deletion window:
   - Add s[l] back to remaining characters.
   - Remove s[l+k] from remaining characters.
5. Maintain duplicates = number of characters with freq >= 2.
6. If duplicates == 0, deletion of length k is possible.
7. If possible(k), search smaller lengths; otherwise larger.

Time: O(N log N)
Space: O(1) - fixed alphabet of 256 characters.
*/


// =====================================================================================================================================================================================

// Two pinter , N

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDeletion(string s)
    {
        int n = s.size();

        vector<int> left(256, 0), right(256, 0);
        int r = n;

        // Longest unique suffix
        while(r > 0 && right[(unsigned char)s[r - 1]] == 0)
        {
            r--;
            right[(unsigned char)s[r]]++;
        }

        int ans = r;

        // Grow unique prefix
        for(int l = 0; l < n; l++)
        {
            unsigned char ch = s[l];

            if(left[ch] > 0)
                break;

            left[ch]++;

            // Remove conflicts from suffix
            while(r < n && right[ch] > 0)
            {
                right[(unsigned char)s[r]]--;
                r++;
            }

            ans = min(ans, r - l - 1);
        }

        return ans;
    }
};

/*
Approach:
1. Remaining string = Prefix + Suffix.
2. Both must be unique and must not share characters.
3. Build longest unique suffix starting at index r.
4. Initially prefix is empty, so answer = r.
5. Grow prefix one character at a time using l.
6. If prefix contains duplicates, stop.
7. If new prefix character exists in suffix,
   move r forward until conflict disappears.
8. Deleted substring = [l+1, r).
   Deletion length = r-l-1.
9. Both l and r move only forward.

Time: O(N)
Space: O(1) - fixed alphabet of 256 characters.
*/


// https://leetcode.com/discuss/post/2716148/starbucks-oa-2023-summer-swe-intern-shor-ywmq/



