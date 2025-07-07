class Solution 
{
public:
    int smallestEvenMultiple(int n) 
    {
        // If n is even, it's already a multiple of 2
        // Else, return 2 * n (LCM of odd number and 2)
        return (n % 2 == 0) ? n : 2 * n;
    }
};

/*
Approach:
- For even n, LCM(2, n) = n
- For odd n, LCM(2, n) = 2 * n
- Return accordingly

Time Complexity: O(1)
Space Complexity: O(1)
*/

// ====================================================================================================

// Approach 2: Generic LCM using GCD
// Time: O(log n), Space: O(1)

class Solution2
{
public:
    int gcd(int a, int b)
    {
        // Euclidean algorithm for GCD
        return b == 0 ? a : gcd(b, a % b);
    }

    int smallestEvenMultiple(int n)
    {
        int two = 2;
        // LCM(a, b) = (a * b) / GCD(a, b)
        return (n * two) / gcd(n, two);
    }
};

/*
Approach:
- Use formula: LCM(a, b) = a * b / GCD(a, b)
- For this problem, a = 2 and b = n
- Works for all values of n

Time Complexity: O(log n) due to GCD
Space Complexity: O(1)
*/
