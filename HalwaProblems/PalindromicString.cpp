#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            // Skip non-alphanumeric
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;

            if (tolower(s[left]) != tolower(s[right]))
                return false;

            left++;
            right--;
        }
        return true;
    }
};

int main() {
    Solution sol;

    cout << "\"A man, a plan, a canal: Panama\" is palindrome? "
         << (sol.isPalindrome("A man, a plan, a canal: Panama") ? "Yes" : "No") << endl;

    cout << "\"race a car\" is palindrome? "
         << (sol.isPalindrome("race a car") ? "Yes" : "No") << endl;

    cout << "\" \" is palindrome? "
         << (sol.isPalindrome(" ") ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- Use two pointers (left and right).
- Skip non-alphanumeric characters.
- Compare characters case-insensitively.

Time Complexity: O(n)
Space Complexity: O(1) (ignoring input string)
*/
