#include <iostream>
using namespace std;

// a^b
long long binaryExponentiation(long long base, long long exponent)
{
    long long result = 1;

    while (exponent > 0)
    {
        // If the current bit is set (odd exponent), multiply result by current base
        if (exponent & 1)
        {
            result *= base;
        }

        // Square the base for the next bit
        base *= base;
        // Move to the next bit (right shift)
        exponent >>= 1;
    }

    return result;
}

// Computes (a^b) % m using binary exponentiation
long long binaryExponentiationMod(long long base, long long exponent, long long mod)
{
    long long result = 1;
    base %= mod;  // Important: reduce base initially

    while (exponent > 0)
    {
        // If the current bit is set (odd exponent), multiply result by current base
        if (exponent & 1)
        {
            result = (result * base) % mod;
        }

        // Square the base and take modulo
        base = (base * base) % mod;

        // Move to the next bit (right shift)
        exponent >>= 1;
    }

    return result;
}

int main()
{
    long long a = 2;
    long long b = 13;

    long long answer = binaryExponentiation(a, b);
    cout << a << "^" << b << " = " << answer << endl;

    a = 2;
    b = 130;
    long long mod = 1e9+7;
    answer = binaryExponentiationMod(a, b, mod);
    cout << "("<< a << "^" << b << ")% "<<mod<<" = " << answer << endl;

    return 0;
}


/**

************************************************************
💡 Key Takeaways:
We go bit by bit from LSB to MSB

Square base each time

Multiply result only when current bit is 1

Efficient O(log b) complexity
************************************************************

🧩 Binary Intuition
Every integer b can be written in binary:

b = 13 → binary: 1101

So:
𝑎^13 = (a^8).(a^4).(a^1)

🔍 Dry Run for binaryExponentiation(2, 13):

Initial:
- base = 2
- exponent = 13 (binary: 1101)
- result = 1

Bitwise traversal from LSB to MSB:

Step 1:
- exponent = 13 → binary = 1101 → LSB = 1 (odd)
- result = result * base = 1 * 2 = 2
- base = base * base = 2 * 2 = 4
- exponent = exponent >> 1 = 6

Step 2:
- exponent = 6 → binary = 110 → LSB = 0 (even)
- result unchanged = 2
- base = 4 * 4 = 16
- exponent = 3

Step 3:
- exponent = 3 → binary = 11 → LSB = 1 (odd)
- result = 2 * 16 = 32
- base = 16 * 16 = 256
- exponent = 1

Step 4:
- exponent = 1 → binary = 1 → LSB = 1 (odd)
- result = 32 * 256 = 8192
- base = 256 * 256 = 65536
- exponent = 0 → DONE

✅ Final result: 2^13 = 8192

We only multiplied result at bit positions where b = 1 → 1101 → bits: [1,0,1,1] → powers used: a^1, a^4, a^8

This gives us:
2^1 = 2  
2^4 = 16  
2^8 = 256  
→ Final: 2 × 16 × 256 = 8192 ✅




Also one important thing - 

(a^b)%m = ? when  b is Large (String) [122222289732973298379827398273982983.......], 
Use Fermat Property:
If:
1) m is prime
2) a and m are coprime

Then:

(a^b)%m = (a^x)%m where x is (b)%(m-1)

This drastically reduces the size of the exponent!
*/
