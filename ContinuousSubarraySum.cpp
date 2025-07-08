class Solution
{
public:
    bool checkSubarraySum(vector<int>& nums, int k)
    {
        unordered_map<int, int> remIndex; // Store first index of each remainder
        int prefix = 0;

        remIndex[0] = -1; // To handle case when subarray starts from index 0

        for (int i = 0; i < nums.size(); ++i)
        {
            prefix += nums[i];
            int rem = prefix % k;

            if (rem < 0) rem += k; // Normalize to positive remainder

            // If this remainder has been seen before
            if (remIndex.count(rem))
            {
                // Check if subarray length is at least 2
                if (i - remIndex[rem] >= 2)
                    return true;
            }
            else
            {
                remIndex[rem] = i; // store the first occurrence only
            }
        }

        return false;
    }
};
/*
Approach:
----------
- Maintain prefix sum and remainder % k.
- If prefix[i] % k == prefix[j] % k, then subarray [j+1...i] is divisible by k.
- Use map to store frequency of seen remainders.
- For strict size ≥ 2, ensure that subarray length >= 2 using indices.

Time: O(n)         (prefix + map)
Space: O(k) or O(n) depending on version
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// If we need to find the count as well then - 

class Solution
{
public:
    int countSubarraySumDivisibleByK(vector<int>& nums, int k)
    {
        unordered_map<int, int> remFreq;       // frequency of remainders
        unordered_map<int, int> firstIndex;    // first index of remainder
        int prefix = 0, count = 0;

        firstIndex[0] = -1;  // base case
        remFreq[0] = 1;

        for (int i = 0; i < nums.size(); ++i)
        {
            prefix += nums[i];
            int rem = prefix % k;
            if (rem < 0) rem += k;

            if (firstIndex.count(rem))
            {
                // i - firstIndex[rem] >= 2 ensures valid subarray length
                if (i - firstIndex[rem] >= 2)
                    count += remFreq[rem];
            }
            else
            {
                firstIndex[rem] = i;
            }

            remFreq[rem]++;
        }

        return count;
    }
};
/*
Approach:
---------
- We keep track of prefix sum % k, and its frequency in remFreq.
- Also store the first index where each remainder is seen (in firstIndex).
- For each index i:
    - If the remainder rem has been seen before at index j, and (i - j) >= 2,
      then any subarray between j+1 to i with that same remainder is valid.
    - We then add remFreq[rem] to the answer.
- remFreq counts how many prefix sums give this remainder.

Why not use rem - k?
---------------------
- Unlike Subarray Sum K, here modulo directly reflects divisibility by k.
- We don’t need to look for `prefix - k`, just match remainders.

Time: O(n)
Space: O(k)
*/
