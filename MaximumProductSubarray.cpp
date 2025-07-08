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

// ==========================================================================================================================================================

// Approach 2


class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        long long maxProduct = LLONG_MIN;  // Final answer
        long long prod = 1;

        // Forward pass
        for (int i = 0; i < nums.size(); i++)
        {
            prod *= nums[i];
            maxProduct = max(maxProduct, prod);
            if (prod == 0)
                prod = 1;  // Reset after zero
        }

        prod = 1;

        // Backward pass
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            prod *= nums[i];
            maxProduct = max(maxProduct, prod);
            if (prod == 0)
                prod = 1;  // Reset after zero
        }

        return (int)maxProduct;
    }
};

/*
Detailed Approach:

- Problem: Find the maximum product of any contiguous subarray.

- Challenge:
  * Negative numbers can flip signs: product may increase or decrease unexpectedly.
  * Zeros break the continuity — any product that includes zero becomes zero.
  * So we can't rely on a single running product the way we do in Kadane's for sum.
  vector<int> nums = {-1, -2, -3, 0, -1, -2};
- Strategy:
  * Traverse the array from left to right, keeping a running product.
    - If product becomes 0, reset it to 1 to start a new subarray.
    - At each step, update the maximum product found so far.

  * Then do the same from right to left.
    - Why backward? Because sometimes the maximum product lies at the right end,
      especially if the number of negative values is even at the end.
    - A single forward pass might miss this if there’s a zero or odd negative count in between.

  * Take the maximum product from both passes.

- Example:
    Input: [-2, 3, -4]
    Forward pass:
      -2 → -6 → 24
    Backward pass:
      -4 → -12 → 24
    Answer: 24

- Time Complexity: O(n)
  One forward and one backward pass through the array.

- Space Complexity: O(1)
  Only variables to store product and max value are used.
*/

