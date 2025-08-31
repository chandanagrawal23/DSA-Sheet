#include <iostream>
using namespace std;

class Solution {
public:
    // 1. Swap using Addition and Subtraction
    void swapAddSub(int &a, int &b) {
        a = a + b;
        b = a - b;
        a = a - b;
    }

    // 2. Swap using Multiplication and Division
    void swapMulDiv(int &a, int &b) {
        if (a == 0 || b == 0) {
            cout << "Multiplication/Division approach not safe for zero values." << endl;
            return;
        }
        a = a * b;
        b = a / b;
        a = a / b;
    }

    // 3. Swap using Bitwise XOR
    void swapXOR(int &a, int &b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
};

int main() {
    Solution sol;

    int x = 10, y = 20;
    sol.swapAddSub(x, y);
    cout << "After swap using Add/Sub: x = " << x << ", y = " << y << endl;

    int m = 5, n = 100;
    sol.swapMulDiv(m, n);
    cout << "After swap using Mul/Div: m = " << m << ", n = " << n << endl;

    int p = 7, q = 12;
    sol.swapXOR(p, q);
    cout << "After swap using XOR    : p = " << p << ", q = " << q << endl;

    return 0;
}

/*
Approach:

1. Addition and Subtraction:
   - a = a + b
   - b = a - b
   - a = a - b
   ✅ No extra space used.
   ⚠️ Risk of overflow if a + b exceeds int limits.

2. Multiplication and Division:
   - a = a * b
   - b = a / b
   - a = a / b
   ✅ No extra space used.
   ⚠️ Not safe if a or b is 0 (division by zero).
   ⚠️ Risk of overflow.

3. Bitwise XOR:
   - a = a ^ b
   - b = a ^ b
   - a = a ^ b
   ✅ Safe for all integers, including negatives and zeros.
   ✅ No overflow risk.
   ✅ Fastest and most reliable in general.

Time Complexity (all methods): O(1)
Space Complexity (all methods): O(1)
*/
