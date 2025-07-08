class Solution
{
public:
    int subarraysDivByK(vector<int>& nums, int k)
    {
        unordered_map<int, int> remFreq; // Stores frequency of remainders
        int prefix = 0, count = 0;

        for (int x : nums)
        {
            prefix += x;
            int rem = prefix % k;

            if (rem < 0) rem += k;  // Normalize to positive remainder
            
            if(rem == 0)
                count++;  // from 0 to i , the sum is divisble by k

            if (remFreq.count(rem))
                count += remFreq[rem];  // Add number of times this remainder has occurred

            remFreq[rem]++;  // Now increment frequency of this remainder
        }

        return count;
    }
};


/*
DETAILED APPROACH: Prefix Sum + Modulo + HashMap
--------------------------------------------------

Goal: Count subarrays where the sum is divisible by K.
That means:
    sum[i..j] % k == 0
=> (prefix[j] - prefix[i-1]) % k == 0
=> prefix[j] % k == prefix[i-1] % k

Key Idea:
- If two prefix sums have the same remainder modulo K,
  their difference is divisible by K.
- So we track how many times each remainder (mod K) has occurred.

Steps:
1. Initialize a map `remFreq` to store frequency of remainders.
   Start with remFreq[0] = 1 to handle the case when prefix itself % k == 0.
2. For each element in array:
    - Add to prefix sum.
    - Compute remainder (prefix % k).
    - Normalize negative remainder to [0, k-1] using: `if (rem < 0) rem += k;`
    - If this remainder has been seen before, then we found subarrays
      ending at current index with sum divisible by K.
3. Return the total count.

Why we **don’t use (prefixSum - k)** as in Subarray Sum = K:
- There, we are looking for an exact difference of `K` between two prefix sums.
- Here, we care about divisibility, so we match **remainders** not exact values.

Comparison with Subarray Sum = K:
----------------------------------
- Both use prefix sum + hashmap.
- Subarray sum K → (prefix - K) match in map.
- Divisible by K  → match of same (prefix % K) in map.

Example:
nums = [4, 5, 0, -2, -3, 1], k = 5
prefix sums: 4, 9, 9, 7, 4, 5
remainders: 4, 4, 4, 2, 4, 0
→ count how many times same remainder seen.

Time: O(n)
Space: O(k) — at most k unique remainders.
*/
