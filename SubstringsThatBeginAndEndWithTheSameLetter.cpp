#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long numberOfSubstrings(string s)
    {
        unordered_map<char, long long> freq;
        long long ans = 0;

        // Step 1: Count frequency of each character
        for (char c : s)
        {
            freq[c]++;
        }

        // Step 2: For each character, add f * (f + 1) / 2
        for (auto &p : freq)
        {
            long long f = p.second;
            ans += f * (f + 1) / 2;
        }

        return ans;
    }
};
/*
Approach:
1. Count the frequency 'f' of each character in the string using a hashmap.
2. For a character with frequency 'f', the number of substrings that start and end 
   with that character is:
       f * (f + 1) / 2
   - Explanation: 
       - Substrings of length 1: f
       - Substrings of length 2: choose 2 occurrences → f-1 + f-2 + ... or combinatorial sum
       - The formula f*(f+1)/2 accounts for all lengths.
3. Sum this value for all characters to get the total number of valid substrings.

Time Complexity: O(N) — traverse string once + 26 chars max for map summation
Space Complexity: O(26) = O(1) — frequency map stores only lowercase letters
*/
