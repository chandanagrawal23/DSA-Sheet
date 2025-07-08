class Solution {
public:
    int maxProduct(vector<int>& nums)
  {
      int n = nums.size();
  
      // Initialize current max, current min, and global max to first element
      int currMax = nums[0];
      int currMin = nums[0];
      int globalMax = nums[0];
  
      for (int i = 1; i < n; ++i)
      {
          // If current number is negative, max becomes min and min becomes max
          if (nums[i] < 0)
          {
              swap(currMax, currMin);
          }
  
          // Extend or restart the max/min product subarray at index i
          currMax = max(nums[i], currMax * nums[i]);
          currMin = min(nums[i], currMin * nums[i]);
  
          // Update global max product
          globalMax = max(globalMax, currMax);
      }
      return globalMax;
  }
};

/*

Approach: Kadane’s Algorithm with a Twist

- The maximum subarray product problem is similar to the maximum subarray sum problem (Kadane's),
  but with **products**, we need to handle **negative numbers** carefully.

Why is this tricky?
- A negative number can turn a big max product into a small one (or vice versa).
- So we maintain:
     currMax = maximum product ending at current index
     currMin = minimum product ending at current index

Why do we need both?
- Because a **negative number can flip signs**:
    → If currMin is negative and we multiply by another negative, it becomes a big positive.
    → Hence, **currMin could help us get a new max** after multiplying by a negative.

 Why do we swap on negative?
- When `nums[i] < 0`, then multiplying by it will swap the roles of max and min:
    → max * nums[i] might become very negative
    → min * nums[i] might become very positive
- So we **swap currMax and currMin before updating**, to reflect this change of roles.

Time Complexity: O(n)
Space Complexity: O(1)

*/
