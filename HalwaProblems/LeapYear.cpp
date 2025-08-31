#include <iostream>
using namespace std;

class Solution {
public:
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

int main() {
    Solution sol;
    cout << "Is 2020 a leap year? " << (sol.isLeapYear(2020) ? "Yes" : "No") << endl;
    cout << "Is 1900 a leap year? " << (sol.isLeapYear(1900) ? "Yes" : "No") << endl;
    cout << "Is 2000 a leap year? " << (sol.isLeapYear(2000) ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- A year is a leap year if:
   - It is divisible by 4 AND not divisible by 100, OR
   - It is divisible by 400

Time Complexity: O(1)
Space Complexity: O(1)
*/
