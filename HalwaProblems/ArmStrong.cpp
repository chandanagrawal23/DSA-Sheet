#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    bool isArmstrong(int n) {
        int original = n, sum = 0;
        int digits = log10(n) + 1;

        while (n > 0) {
            int digit = n % 10;
            sum += pow(digit, digits);
            n /= 10;
        }

        return sum == original;
    }
};

int main() {
    Solution sol;
    cout << "Is 153 Armstrong? " << (sol.isArmstrong(153) ? "Yes" : "No") << endl;
    cout << "Is 370 Armstrong? " << (sol.isArmstrong(370) ? "Yes" : "No") << endl;
    cout << "Is 123 Armstrong? " << (sol.isArmstrong(123) ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- Count digits in the number (d)
- Sum each digit raised to the power d
- Compare the result with original number

Time Complexity: O(d), where d is number of digits (log10(n))
Space Complexity: O(1)
*/
