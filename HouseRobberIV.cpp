class Solution {
public:
    // Function to check if we can steal 'k' houses with the given 'mid' capability.
    bool canSteal_K_Houses_WithMidCapability(vector<int>& nums, int k, int mid)
    {
        int i = 0, n = nums.size();
        
        // Iterate through the houses (nums)
        while(i < n)
        {
            // If current house's capability is less than or equal to 'mid', we can steal it
            if(nums[i] <= mid)
            {
                k--;    // Decrease the number of houses we still need to steal
                i += 2; // Skip the next house, as we can't steal two adjacent houses
            }
            else
            {
                i++;  // Move to the next house if the current house is too difficult to steal
            }

            // If we have stolen 'k' houses, return true
            if(k == 0) 
                return true;
        }

        // Return true if we managed to steal exactly 'k' houses
        return k == 0;
    }

    // Main function to find the minimum capability required to steal 'k' houses
    int minCapability(vector<int>& nums, int k) 
    {
        int n = nums.size();
        int lo = 0, hi = 1e9 + 1;  // Initial range for binary search
        int ans = -1;  // Variable to store the answer

        // Perform binary search to find the minimum capability
        while(lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;  // Calculate mid point

            // Check if it's possible to steal 'k' houses with 'mid' capability
            if(canSteal_K_Houses_WithMidCapability(nums, k, mid))
            {
                ans = mid;   // If possible, update the answer with the current 'mid'
                hi = mid - 1;  // Try to find a smaller value of 'mid' by adjusting the high bound
            }
            else
            {
                lo = mid + 1;  // If not possible, try a larger value by adjusting the low bound
            }
        }
        
        // Return the minimum capability that allows stealing 'k' houses
        return ans;
    }
};
