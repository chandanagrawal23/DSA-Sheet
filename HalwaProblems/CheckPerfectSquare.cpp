#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    bool isPerfectSquare(int n) {
        int root = sqrt(n);
        return root * root == n;
    }
};

int main() {
    Solution sol;
    cout << "Is 144 a perfect square? " << (sol.isPerfectSquare(144) ? "Yes" : "No") << endl;
    cout << "Is 150 a perfect square? " << (sol.isPerfectSquare(150) ? "Yes" : "No") << endl;
    cout << "Is 1 a perfect square? " << (sol.isPerfectSquare(1) ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- Find the integer square root of n using sqrt().
- Check if (root * root) == n

Time Complexity: O(1)
Space Complexity: O(1)
*/
