class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums) 
   {
        int n = nums.size();
        stack<int> s;

        // count[i] stores the number of valid subarrays ending at index i
        // basically count[i] says how many subarrays start's and end at index "i" whose max value is nums[i]

        vector<int> count(n, 1); // Every element itself forms a valid subarray of size 1

        for (int i = 0; i < n; i++) 
        {
            // Maintain a monotonic decreasing stack
            while (!s.empty() && nums[s.top()] <= nums[i]) 
            {
                // If previous value is equal to current value,
                // we can extend all valid subarrays ending at that index
                if (nums[s.top()] == nums[i]) 
                {
                    count[i] += count[s.top()];
                }
                // Pop all values smaller or equal (<=) to maintain decreasing order
                s.pop();
            }

            // Push current index into the stack
            s.push(i);
        }

        // Return the total number of valid subarrays
        // Sum over all valid subarrays ending at each index
        long long totalSum = 0;
        for(int x : count)
            totalSum += 1LL*x;

        return totalSum;
    }
};

/*

Idea:
   - Use a monotonic decreasing stack to track blocks of the same maximum value
   - Maintain a count array:
     → count[i] = number of valid subarrays ending at index i

For each index i:
   - Start with count[i] = 1 (subarray [nums[i]] is always valid)
   - If previous element(s) are ≤ nums[i], pop them
     → If equal, merge their count into current (because [max, ..., max] can form subarrays)

-----------------------------------------------------------
remember stack contain Indexes Not values
-----------------------------------------------------------------
Ex : nums = [3,1,2,3,1,2,3,3]

| i | nums [i] | Stack Before |                             Action                           | Stack After | count [i] |
| - | -------- | ------------ | -----------------------------------------------------------  | ----------- | --------- |
| 0 | 3        |  []          | push 0                                                       |  [0]        | 1         |
| 1 | 1        |  [0]         | push 1                                                       |  [0, 1]     | 1         |
| 2 | 2        |  [0, 1]      | 2 > 1 → pop 1                                                |  [0, 2]     | 1         |
| 3 | 3        |  [0, 2]      | 3 > 2 → pop 2, 3 == 3 → pop 0 (equal) → count[3] += count[0] |  [3]        | 2         |
| 4 | 1        |  [3]         | push 4                                                       |  [3, 4]     | 1         |
| 5 | 2        |  [3, 4]      | 2 > 1 → pop 4                                                |  [3, 5]     | 1         |
| 6 | 3        |  [3, 5]      | 3 > 2 → pop 5, 3 == 3 → pop 3 (equal) → count[6] += count[3] |  [6]        | 3         |
| 7 | 3        |  [6]         | 3 == 3 → pop 6 (equal) → count[7] += count[6]                |  [7]        | 4         |

Total = 1 + 1 + 1 + 2 + 1 + 1 + 3 + 4 = 14 

*/
