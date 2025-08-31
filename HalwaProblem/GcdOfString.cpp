#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if (str1 + str2 != str2 + str1)
            return "";

        return str1.substr(0, gcd(str1.length(), str2.length()));
    }

private:
    int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
};

int main() {
    Solution sol;

    cout << "GCD of ABCABC and ABC: " << sol.gcdOfStrings("ABCABC", "ABC") << endl;
    cout << "GCD of ABABAB and ABAB: " << sol.gcdOfStrings("ABABAB", "ABAB") << endl;
    cout << "GCD of LEET and CODE: " << sol.gcdOfStrings("LEET", "CODE") << endl;

    return 0;
}

/*
Approach:
- If str1 + str2 != str2 + str1, then no common divisor string.
- Otherwise, the answer is substring from 0 to GCD of lengths.

Time Complexity: O(n + m), where n and m are lengths of str1 and str2
Space Complexity: O(1)
*/
