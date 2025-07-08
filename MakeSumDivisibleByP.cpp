#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;
        for (int num : nums) 
          total += num;

        int mod = total % p;
        if (mod == 0) return 0;  // already divisible, no removal needed

        unordered_map<int, int> lastSeen;
        lastSeen[0] = -1;  // base case: prefix sum % p == 0 at index -1

        int result = nums.size();
        long long prefix = 0;

        for (int i = 0; i < nums.size(); ++i) {
            prefix = (prefix + nums[i]) % p;

            // we want to find a previous prefix such that
            // currentPrefix - previousPrefix ≡ mod (mod p)
            int diff = prefix - mod;
            if (diff < 0) 
                diff += p; // to handle neg modulo
            int want = diff % p;

            if (lastSeen.count(want))
                result = min(result, i - lastSeen[want]);

            // update current prefix mod and its index
            lastSeen[prefix] = i;
        }

        return result == nums.size() ? -1 : result;
    }
};

/*
APPROACH:
---------
We are given an array of positive integers `nums`, and we want to remove the smallest subarray 
(possibly empty) such that the remaining sum is divisible by p.

Let:
- S = total sum of the array
- We want: (S - sum(subarray)) % p == 0
          → sum(subarray) % p == S % p
          → let say mod = S % p
          → that means we want sum(subarray) % p  = mod
          
Now the problem reduces to: 
- Find the shortest subarray whose sum % p == mod

To solve:
- Keep a running prefix sum modulo p
- Use a hashmap to store: {prefixSum % p → index}
- For current prefix modulo, check if there's a previously seen prefix
  such that (currentPrefix - previousPrefix) % p == mod
- If yes, update answer with the length between them

WHY WE DON'T DO (mod - k) in this case:
---------------------------------------
In Subarray Sum == K:
→ We check for prefixSum - K because sum(i..j) = prefix[j] - prefix[i-1]

Here:
→ We use modulo arithmetic, and must handle negative mods correctly:
   → So we compute: (prefix - mod + p) % p to avoid negatives

COMPARISON:
------------
🔹 *Subarray Sum = K*:
    - We want sum of subarray = K → prefix - K
    - Straightforward subtraction

🔹 *This problem*:
    - We want sum of subarray ≡ mod (mod p)
    - Need to use modular arithmetic, so we search: (prefix - mod + p) % p
    - We cannot use (mod - prefix + p) % p or rem - k directly, because we are
      not looking for an *exact* prefix value, but a prefix that satisfies the modular relationship

TIME & SPACE:
-------------
Time:  O(n)
Space: O(p) (map stores at most p mod values)

*/
