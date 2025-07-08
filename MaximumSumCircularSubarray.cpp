class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int totalSum = 0;
        int maxSum = INT_MIN, curMax = 0;
        int minSum = INT_MAX, curMin = 0;

        for (int num : nums) {
            totalSum += num;

            // Standard Kadane for max subarray sum
            curMax = max(num, curMax + num);
            maxSum = max(maxSum, curMax);

            // Kadane for min subarray sum (used for circular)
            curMin = min(num, curMin + num);
            minSum = min(minSum, curMin);
        }

        // If all elements are negative, maxSum is correct (don't use circular)
        if (maxSum < 0) return maxSum;

        return max(maxSum, totalSum - minSum);
    }
}; 

/*
Approach:

1. We want to find the maximum subarray sum in a circular array.
2. Two cases arise:
   a. The subarray does **not wrap around** → Use Kadane's algorithm.
   b. The subarray **wraps around** → We take total sum - min subarray sum.

3. For (b), wrapping means:
   - We're excluding the **worst subarray (minimum sum)** in the middle.
   - So the wraparound max = totalSum - minSubarraySum.

4. Edge Case:
   - If all numbers are negative, wrapping will return 0.
   - But we must take at least one number → so we return maxSum directly.

Time: O(n)
Space: O(1)
*/
