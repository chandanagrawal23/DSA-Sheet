#include <iostream>
using namespace std;

class Solution {
public:
    long long factorial(int n) {
        long long result = 1;
        for (int i = 2; i <= n; ++i)
            result *= i;
        return result;
    }
};

int main() {
    Solution sol;
    cout << "Factorial of 5: " << sol.factorial(5) << endl;
    cout << "Factorial of 10: " << sol.factorial(10) << endl;
    cout << "Factorial of 0: " << sol.factorial(0) << endl;

    return 0;
}

/*
Approach:
- Multiply numbers from 2 to n in a loop to compute factorial.

Time Complexity: O(n)
Space Complexity: O(1)
*/
