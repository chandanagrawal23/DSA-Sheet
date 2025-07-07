class Solution 
{
public:
    string addStrings(string num1, string num2) 
    {
        int i = num1.length() - 1;  
        int j = num2.length() - 1;  
        int carry = 0;              
        string result = "";         

        // Loop until both strings are processed and no carry remains
        while (i >= 0 || j >= 0 || carry)
        {
            // Extract current digits or use 0 if index out of bounds
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

            // Calculate sum of digits and carry
            int sum = digit1 + digit2 + carry;

            // Append current digit (unit place) to the front of result
            result = char((sum % 10) + '0') + result;

            // Update carry for next iteration
            carry = sum / 10;
        }

        return result;
    }
};

/*
Approach:
- Use two pointers to process both strings from right to left (least significant digit first).
- Add digit by digit along with the carry.
- If lengths are unequal, treat the shorter one as having leading zeros.
- Store the result in reverse (prepending) to keep the correct order.

Time Complexity: O(max(n, m)), where n and m are lengths of num1 and num2
Space Complexity: O(max(n, m)), for storing the result string
*/
