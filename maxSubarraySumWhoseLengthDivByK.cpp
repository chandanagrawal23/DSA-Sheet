class Solution {
 public:
    int maxSubarraySum(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
    
        // Build prefix sum array
        for (int i = 0; i < n; ++i)
        {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    
        int maxSum = INT_MIN;
    
        // Try all k starting offsets: 0, 1, ..., k-1
        for (int offset = 0; offset < k; ++offset)
        {
            int currSum = 0;
    
            // Step through prefix[] using stride k
            for (int i = offset; i + k <= n; i += k)
            {
                int subarraySum = prefix[i + k] - prefix[i];
    
                // Either start fresh or extend the previous group
                currSum = max(subarraySum, currSum + subarraySum);
    
                maxSum = max(maxSum, currSum);
            }
        }
    
        return maxSum;
    }
};
/*

🔍 Approach:

- Construct a prefix sum array: prefix[i] = sum of nums[0] to nums[i-1]
- Then group subarrays based on their start positions modulo k:
  Group 0: indices 0, k, 2k...
  Group 1: indices 1, k+1, 2k+1...
  ...
  Group k-1: ...

- For each group, apply Kadane’s algorithm over the stride-k intervals:
  Use the difference of prefix sums to get subarray sums of size k.

- This ensures that we only consider subarrays of size divisible by k,
  and maximize their sum efficiently.

📌 For k = 4, we try subarrays at:
   - [0,4,8,...]
   - [1,5,9,...]
   - [2,6,10,...]
   - [3,7,11,...]

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) for prefix sum array

*/
