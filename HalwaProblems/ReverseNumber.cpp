#include <iostream>
using namespace std;

class Solution {
public:
    int reverseNumber(int n) {
        int rev = 0;
        while (n != 0) {
            rev = rev * 10 + n % 10;
            n /= 10;
        }
        return rev;
    }
};

int main() {
    Solution sol;
    cout << "Reverse of 12345: " << sol.reverseNumber(12345) << endl;
    cout << "Reverse of 500: " << sol.reverseNumber(500) << endl;
    cout << "Reverse of 0: " << sol.reverseNumber(0) << endl;

    return 0;
}

/*
Approach:
- Extract digits using modulus (%) and build reversed number by multiplying current result by 10 and adding new digit.

Time Complexity: O(log10(n)) → Number of digits in n
Space Complexity: O(1)
*/
