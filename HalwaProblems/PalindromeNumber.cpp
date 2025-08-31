#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false; // Negative numbers can't be palindrome

        int original = x;
        long reversed = 0;

        while (x != 0) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }

        return reversed == original;
    }
};

int main() {
    Solution sol;

    cout << "121 is palindrome? " << (sol.isPalindrome(121) ? "Yes" : "No") << endl;
    cout << "-121 is palindrome? " << (sol.isPalindrome(-121) ? "Yes" : "No") << endl;
    cout << "10 is palindrome? " << (sol.isPalindrome(10) ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- Reverse the integer and compare with the original.
- Return false if it's negative (since the '-' sign makes it non-palindromic).

Time Complexity: O(log10(n)) => number of digits
Space Complexity: O(1)
*/
