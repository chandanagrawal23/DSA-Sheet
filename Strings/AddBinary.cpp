class Solution 
{
public:
    string addBinary(string a, string b)
    {
        string result = "";           // Resultant binary string
        int carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;

        // Loop until both strings and carry are processed
        while (i >= 0 || j >= 0 || carry)
        {
            if (i >= 0) 
                carry += a[i--] - '0';  // Add bit from a
            if (j >= 0) 
                carry += b[j--] - '0';  // Add bit from b

            result = char((carry % 2) + '0') + result;  // Append bit

            carry /= 2;  // Update carry
        }

        return result;
    }
};

/*
Approach:
- Start from the end of both strings.
- Add corresponding bits and carry.
- Append current bit to result and update carry.
- Continue until all bits and carry are processed.

Time Complexity: O(max(n, m)), where n and m are lengths of a and b
Space Complexity: O(max(n, m)), for storing the result
*/
