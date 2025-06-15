// Below is for finding the SQRT in int , like sqrt(10) = 3
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) return x;  // Edge cases

        long long low = 1, high = x;
        long long result = 0;

        // Binary search to find floor(sqrt(x))
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long square = mid * mid;

            if (square == x) {
                return mid;  // Exact square root
            }
            else if (square < x) {
                result = mid;  // Store candidate and search right
                low = mid + 1;
            }
            else {
                high = mid - 1;  // Search left
            }
        }

        return result;  // Closest integer sqrt
    }
};
/*
Approach Summary:
- Binary search on range [1, x] to find the largest integer `mid` such that mid^2 <= x.
- If mid^2 == x, return mid directly.
- If mid^2 < x, search on right half and keep `mid` as possible result.
- If mid^2 > x, search on left half.
- Time complexity: O(log x)
- Space complexity: O(1)
*/





// Below is for finding the SQRT in float too , like sqrt(10) = 3.1622

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double preciseSqrt(int x, int precision = 6) {
        if (x == 0 || x == 1) return x;

        double low = 0, high = x, mid;

        // Step 1: Binary Search for Integer Part
        while (high - low > 1e-6) {  // Use a very small threshold
            mid = (low + high) / 2;
            if (mid * mid <= x)
                low = mid;
            else
                high = mid;
        }

        // Round result to required decimal precision
        double factor = pow(10, precision);
        return round(low * factor) / factor;
    }
};

int main() {
    Solution sol;
    double sqrtValue = sol.preciseSqrt(10, 6);
    cout << fixed << setprecision(6) << "√10 ≈ " << sqrtValue << endl;
    return 0;
}

/*
🔹 Short Approach:
- Use binary search between [0, x] to find square root with precision.
- Stop when the difference between high and low is very small (e.g., 1e-6).
- Round the result to the given decimal places using scaling and `round()`.
*/
