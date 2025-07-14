class Solution 
{
public:
    string toHex(int num) 
    {
        // Convert signed int to unsigned to handle negatives properly
        unsigned int value = num;

        // Array of hexadecimal characters
        char hexChars[17] = "0123456789abcdef";

        string hexStr;

        // Convert value to hex (base 16)
        do 
        {
            int remainder = value % 16;
            hexStr += hexChars[remainder]; // Append corresponding hex character
            value /= 16;
        } 
        while (value);

        // Reverse to get correct order
        return {hexStr.rbegin(), hexStr.rend()};
    }
};
/*
Problem:
--------
Convert a 32-bit signed integer into a hexadecimal string (lowercase, no leading "0x").

Key Insight:
------------
- Negative numbers are converted to their 2's complement form if cast to unsigned.
  Ex: -1 becomes 0xFFFFFFFF (which is 2^32 - 1)

Approach:
---------
1. Convert the signed `int` to `unsigned int` to correctly handle negative values.
2. Repeatedly divide the number by 16 (hex base), and collect the remainder.
3. Use `hexChars[remainder]` to get the corresponding hexadecimal digit.
4. Append characters in reverse order, so we reverse the final string.

Example:
--------
Input: -1
Unsigned value: 4294967295 (2^32 - 1)
Hex: "ffffffff"

Time Complexity: O(1) — Max of 8 digits in 32-bit hex
Space Complexity: O(1) — Uses fixed space

*/
