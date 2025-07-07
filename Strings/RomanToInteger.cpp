class Solution 
{
public:
    int romanToInt(string s) 
    {
        unordered_map<char, int> roman = {
            { 'I', 1 },
            { 'V', 5 },
            { 'X', 10 },
            { 'L', 50 },
            { 'C', 100 },
            { 'D', 500 },
            { 'M', 1000 }
        };

        int sum = roman[s.back()];  // Start from last character

        // Traverse the string from second last to first
        for (int i = s.length() - 2; i >= 0; --i) 
        {
            // If current symbol is less than the one after it, subtract
            if (roman[s[i]] < roman[s[i + 1]])
            {
                sum -= roman[s[i]];
            }
            else
            {
                sum += roman[s[i]];  // Else, just add it
            }
        }

        return sum;
    }
};

/*
Approach:
- Traverse the string from end to start.
- Start with last symbol's value in the result.
- If the current Roman numeral is smaller than the one to its right,
  subtract it (like IV = 5 - 1).
- Else, add it normally.

Time Complexity: O(n), where n = length of the string
Space Complexity: O(1), since the map has constant size (7 entries)
*/
