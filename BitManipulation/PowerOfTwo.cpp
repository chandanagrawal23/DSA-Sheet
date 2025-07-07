// Approach 1: Loop Division by 2
// Time: O(log n), Space: O(1)

class Solution
{
public:
    bool isPowerOfTwo(int n) 
    {
        if (n <= 0) return false;
        while (n % 2 == 0)
        {
            n /= 2;
        }
        return n == 1;
    }
};

// ====================================================

// Approach 2: Bit Manipulation (n & (n-1))
// Time: O(1), Space: O(1)

class Solution
{
public:
    bool isPowerOfTwo(int n) 
    {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;  // Only one bit set
    }
};

// ====================================================

// Approach 3: Built-in popcount (exactly one set bit)
// Time: O(1), Space: O(1)

class Solution
{
public:
    bool isPowerOfTwo(int n) 
    {
        if (n <= 0) return false;
        return __builtin_popcount(n) == 1;
    }
};

// ====================================================

// Approach 4: Using bitset count == 1
// Time: O(1), Space: O(1)

#include <bitset>

class Solution 
{
public:
    bool isPowerOfTwo(int n) 
    {
        if (n <= 0) return false;
        return bitset<32>(n).count() == 1;
    }
};
