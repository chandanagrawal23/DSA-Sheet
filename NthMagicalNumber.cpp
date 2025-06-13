class Solution
{
public:
    // Return GCD of two numbers
    int gcd(int x, int y)
    {
        if (x == 0) return y;
        return gcd(y % x, x);
    }

    int nthMagicalNumber(int n, int a, int b)
    {
        const int mod = 1e9 + 7;
        long long lcm = (1LL * a / gcd(a, b)) * b;

        long long left = 1, right = 1e18;
        int ans = -1;

        while (left <= right)
        {
            long long mid = left + (right - left) / 2;

            long long count = mid / a + mid / b - mid / lcm;

            if (count >= n)
            {
                ans = mid;         // possible answer
                right = mid - 1;   // try smaller
            }
            else
            {
                left = mid + 1;    // need more magical numbers
            }
        }

        return ans % mod;
    }
};

/*

Approach:
---------
We are to find the Nth number divisible by either A or B.

1. Use binary search over the answer space: from 1 to 1e18.
2. For a mid value, count how many numbers ≤ mid are divisible by A or B:
   count = mid / A + mid / B - mid / LCM(A, B)
   (Subtracting common multiples to avoid double-counting)

3. If count ≥ N → we found a candidate, but we try to minimize → move left
4. Else → we need a bigger value → move right

Why left ≤ right version:
- Helps in cleaner bounds and capturing the exact value (especially when answer needs minimizing or maximizing with condition)

Time: O(log(1e18)) ≈ 60 iterations  
Space: O(1)

*/
