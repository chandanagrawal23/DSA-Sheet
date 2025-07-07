class Solution 
{
public:
    bool isAnagram(string s, string t) 
    {
        // If lengths differ, cannot be anagrams
        if (s.length() != t.length())
            return false;

        vector<int> count(26, 0);  // Frequency array for 'a' to 'z'

        for (char c : s) 
            count[c - 'a']++;      // Count characters in s

        for (char c : t) 
            count[c - 'a']--;      // Subtract counts using t

        for (int freq : count)
            if (freq != 0) return false;  // If any count non-zero, not anagram

        return true;
    }
};

/*
Approach:
- Use a frequency array of size 26 to track character counts.
- Increment for string `s`, decrement for string `t`.
- If all frequencies are zero, then both strings are anagrams.

Time Complexity: O(n)
Space Complexity: O(1) — constant space for 26 lowercase letters
*/
