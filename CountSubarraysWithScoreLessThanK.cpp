class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) 
    {
        long long windowSum = 0, totalCount = 0;
        int left = 0;
        
        // Two pointers: left and right to define the sliding window
        for (int right = 0; right < nums.size(); ++right) 
        {
            windowSum += nums[right]; // Expand the window by including nums[right]
            
            // Shrink the window from the left as long as the condition is violated
            // Condition: (windowSum * windowLength) should be < k
            while (windowSum * (right - left + 1) >= k)
            {
                windowSum -= nums[left];  // Exclude nums[left]
                left++; //  and move left forward
            }
                
            
            // All subarrays ending at 'right' and starting from [left, right] are valid
            // like [left, right] , [left+1,right] ......... [right,right]
            // Their count is (right - left + 1)
            totalCount += right - left + 1;
        }

        // Return the total number of valid subarrays
        return totalCount;
    }
};


/*

Approach:
---------
We need to count how many subarrays have:
    average(subarray) < k / length(subarray)
⇒ Multiply both sides: sum(subarray) < k

So, the condition becomes:
    sum(nums[left..right]) * length < k
    i.e., windowSum * (right - left + 1) < k

Steps:
1. Use a sliding window [left..right] to traverse the array.
2. For each `right`, add nums[right] to the window sum.
3. While the product of windowSum and window length violates the constraint, 
   move `left` forward and shrink the window.
4. For each valid window, we can form (right - left + 1) valid subarrays ending at `right`.

Why (right - left + 1)?
→ Because all subarrays starting from:
   - left to right
   - left+1 to right
   - ...
   - right to right
   are valid and distinct.

Time Complexity: O(n)
- Each element is added and removed from the window at most once

Space Complexity: O(1)
- Constant extra space (just pointers and a few counters)

*/
