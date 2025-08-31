#include <iostream>
using namespace std;

class Solution {
public:
    // 1. Using formula: n(n+1)/2
    int sumOfFirstN_Formula(int n) {
        return n * (n + 1) / 2;
    }

    // 2. Using loop
    int sumOfFirstN_Loop(int n) {
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += i;
        }
        return sum;
    }
};

int main() {
    Solution sol;

    int testCases[] = {10, 100, 0};

    for (int n : testCases) {
        cout << "\n--- N = " << n << " ---" << endl;
        cout << "Sum using formula: " << sol.sumOfFirstN_Formula(n) << endl;
        cout << "Sum using loop   : " << sol.sumOfFirstN_Loop(n) << endl;
    }

    return 0;
}
