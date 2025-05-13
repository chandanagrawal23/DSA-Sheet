/*
This can be solved by array or map, but here we are solving using BIT manipulation so make sure you do/try same.

*/
class Solution {
public:
    char repeatedCharacter(string s) {
        int mask = 0;  // Bitmask to track seen characters

        for (char ch : s) {
            int bit = 1 << (ch - 'a');  // Shift 1 by the position of the character
            if (mask & bit)  // If the bit is already set → character repeated
                return ch;
            mask |= bit;  // Mark this character as seen by setting the bit
        }

        return '%';  // Default return (won’t be hit as per problem constraints)
    }
};

/*

Approach:

- Use a 26-bit integer `mask` as a bitmap to track lowercase letters (a-z).
- For each character:
    - Check if its bit is already set → if yes, it’s the first repeated character.
    - Else, set its bit in the mask.
- Efficient as it avoids using extra data structures like hash sets.

Time Complexity: O(n)  
Space Complexity: O(1) — uses only an integer for tracking

*/
