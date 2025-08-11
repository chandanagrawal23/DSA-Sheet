class Solution
{
public:
    vector<int> productQueries(int n, vector<vector<int>>& q)
    {
        const int MOD = 1e9 + 7;
        vector<int> MinPower2, ans;

        // build MinPower2 from set bits of n
        for (int i = 0; i < 32; ++i)
        {
            if (n & (1 << i))            // if bit i is set
                MinPower2.push_back(1 << i); // store 2^i
        }

        // process each query
        for (auto &x : q)
        {
            int L = x[0], R = x[1];
            long long prod = MinPower2[L]; // start with first element in range
            for (int j = L + 1; j <= R; ++j)
                prod = (prod * MinPower2[j]) % MOD; // multiply and mod
            ans.push_back(prod);
        }
        return ans;
    }
};

/*
Approach:
1. Decompose n into its set bits → store corresponding powers of 2 in MinPower2.
    A. Convert n (the exponent) into binary form.
       - Every number can be expressed as sum of powers of 2.
       - Example: n = 13 → binary = 1101
         This means: 13 = 8 + 4 + 1  →  2^3 + 2^2 + 2^0
    
    B. For each set bit (bit = 1) in n's binary form:
       - Determine the power of 2 it represents.
       - Store that power of 2 in MinPower2 array (or list).
    
       Example:
         n = 13 (1101)
         Bits from right to left:
           bit0 = 1 → 2^0 = 1
           bit2 = 1 → 2^2 = 4
           bit3 = 1 → 2^3 = 8
         MinPower2 = [1, 4, 8]
2. For each query [L, R], multiply elements in MinPower2 from L to R, taking modulo 1e9+7.
3. Direct loop for multiplication (can be optimized with prefix products for O(1) queries).

Time Complexity: O(32 + Q*K)  where K = avg length of query range
Space Complexity: O(32) for MinPower2 + O(Q) for answer
*/
