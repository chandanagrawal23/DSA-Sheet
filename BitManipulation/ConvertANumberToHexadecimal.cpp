class Solution 
{
public:
    string toHex(int num) 
    {
        if (num == 0)
        {
            return "0";
        }

        string hexMap = "0123456789abcdef";
        unsigned int val = num;

        // Handle negative numbers by converting to unsigned 32-bit equivalent
        if (num < 0)
        {
            val = static_cast<unsigned int>(num) + (1LL << 32);
        }

        string result;
        while (val > 0)
        {
            int rem = val % 16;
            result = hexMap[rem] + result;
            val /= 16;
        }

        return result;
    }
};

/*
Problem:
--------
Convert an integer to a hexadecimal string.

Logic:
------
- If the number is zero, return "0".
- If the number is negative, convert it to its 32-bit unsigned equivalent:
     num + 2^32 (same as unsigned int behavior).
- Repeatedly divide by 16 and prepend the corresponding hex digit.

Hex Digits:
-----------
Use the string "0123456789abcdef" to get the digit for each remainder.

Example:
--------
Input: -1
Unsigned version: 4294967295 (2^32 - 1)
Output: "ffffffff"

Time Complexity: log16(N) ~ O(1) — At most 8 hex digits (32 bits)
Space Complexity: O(1)

*/
