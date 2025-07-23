class Solution
{
public:
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();

        // Prefix sum to compute range sums in O(1)
        vector<long long> preSum(n);
        preSum[0] = nums[0];

        for (int i = 1; i < n; ++i)
        {
            preSum[i] = preSum[i - 1] + nums[i];
        }

        // Map to store the last index where each number was seen
        unordered_map<int, int> lastIndex;

        long long maxSum = LLONG_MIN;

        for (int right = 0; right < n; ++right)
        {
            // We are checking if there exists any left index such that
            // abs(nums[right] - nums[left]) == k
            // This is same as checking:
            // nums[left] == nums[right] - k  OR  nums[left] == nums[right] + k
            int need1 = nums[right] - k;
            int need2 = nums[right] + k;

            // Check if any subarray ending at current index has valid left index
            if (lastIndex.count(need1))
            {
                int left = lastIndex[need1];
                long long sum;
              
                if(left > 0)
                    sum = preSum[right] - preSum[left - 1];
                else
                    sum = preSum[right];
              
                maxSum = max(maxSum, sum);
            }

            if (lastIndex.count(need2))
            {
                int left = lastIndex[need2];
                long long sum;
              
                if(left > 0)
                    sum = preSum[right] - preSum[left - 1];
                else
                    sum = preSum[right];
              
                maxSum = max(maxSum, sum);
            }

            // Store only the first or best index with smaller prefix sum for current value
            if (!lastIndex.count(nums[right]) || preSum[lastIndex[nums[right]]] > preSum[right])
            {
                lastIndex[nums[right]] = right;
            }
        }

        return (maxSum == LLONG_MIN) ? 0 : maxSum;
    }
};

/*
Approach:

- We're looking for the maximum sum of a subarray where the absolute difference
  between the first and last element is exactly `k`.

- For every index `right`, we check if there exists an earlier index `left` such that:
      abs(nums[right] - nums[left]) == k

  → This condition can be rewritten as:
      nums[left] == nums[right] - k   or   nums[right] + k

  → So we calculate:
      - `need1 = nums[right] - k`
      - `need2 = nums[right] + k`

  → We check if either `need1` or `need2` exists in a map `lastIndex` that stores
    the last seen index for each value.

- To compute the subarray sum from `left` to `right` in constant time,
  we precompute the prefix sum `preSum`:
      preSum[i] = sum of nums[0..i]

  Subarray sum from `left` to `right`:
      if left > 0 → sum = preSum[right] - preSum[left - 1]
      else        → sum = preSum[right]

- "Why do we update only if current prefix is smaller?"

  We want to "maximize" `preSum[right] - preSum[left - 1]`.  
  This means we want to minimize `preSum[left - 1]`.

  So:
      - If we’ve seen this value `val` before,
        but `preSum[current] < preSum[old index]`, then we update it.

- Edge Case:
  → If no good subarray is found (i.e., maxSum was never updated), return 0.

Time Complexity: O(n)
- O(n) for prefix sum
- O(n) for main iteration + hashmap lookup

Space Complexity: O(n)
- For prefix sum and hash map
*/
