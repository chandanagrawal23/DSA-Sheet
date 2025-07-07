class Solution 
{
public:
    string intToRoman(int num) 
    {
        string result = "";

        // Value-symbol pairs in descending order
        vector<pair<int, string>> roman = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100,  "C"}, {90,  "XC"}, {50,  "L"}, {40,  "XL"},
            {10,   "X"}, {9,   "IX"}, {5,   "V"}, {4,   "IV"},
            {1,    "I"}
        };

        for (const auto& [value, symbol] : roman)
        {
            while (num >= value)
            {
                result += symbol;
                num -= value;
            }
        }

        return result;
    }
};

/*
Approach:
- Store (value, symbol) pairs in a vector of pairs, sorted in descending order.
- For each pair, subtract the value and append the symbol to the result string
  as long as the current number is ≥ value.

Time Complexity: O(1)
Space Complexity: O(1)
*/
