// Approach 1: Basic Bit Traversal using Right Shift
// Time: O(32), Space: O(1)

class Solution 
{
public:
    int hammingWeight(uint32_t n) 
    {
        int count = 0;
        while (n > 0)
        {
            if (n & 1) count++;  // Check if LSB is 1
            n >>= 1;             // Right shift by 1 bit
        }
        return count;
    }
};

// ========================================================================================================================================

// Approach 2: Brian Kernighan’s Algorithm
// Time: O(k), where k = number of set bits, Space: O(1)

class Solution
{
public:
    int hammingWeight(uint32_t n) 
    {
        int count = 0;
        while (n > 0)
        {
            count++;
            n &= (n - 1);  // Clear the lowest set bit
        }
        return count;
    }
};

// ========================================================================================================================================

// Approach 3: Using __builtin_popcount (GCC/Clang)
// Time: O(1), Space: O(1)

class Solution
{
public:
    int hammingWeight(uint32_t n) 
    {
        return __builtin_popcount(n);  // Built-in function to count set bits
    }
};

// ========================================================================================================================================

// Approach 4: Using bitset STL
// Time: O(1), Space: O(1)

#include <bitset>

class Solution
{
public:
    int hammingWeight(uint32_t n) 
    {
        return bitset<32>(n).count();  // Convert to bitset and count 1s
    }
};
