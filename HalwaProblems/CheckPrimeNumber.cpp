#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;

        // Loop from 2 to sqrt(n)
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0)
                return false;
        }

        return true;
    }
};

int main() {
    Solution sol;

    cout << "Is 29 prime? " << (sol.isPrime(29) ? "Yes" : "No") << endl;
    cout << "Is 42 prime? " << (sol.isPrime(42) ? "Yes" : "No") << endl;
    cout << "Is 1 prime? " << (sol.isPrime(1) ? "Yes" : "No") << endl;

    return 0;
}

/*
Approach:
- A number n is prime if it is greater than 1 and divisible only by 1 and itself.
- For optimization, we loop from 2 to sqrt(n) instead of 2 to n-1.
  - This is because a larger factor of n must be paired with a smaller one already checked.
- If we find any number in this range that divides n, it's not prime.

Time Complexity:
- O(√n), since we only check up to the square root of n.

Space Complexity:
- O(1), constant space used.
*/
