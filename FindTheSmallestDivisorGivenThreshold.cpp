class Solution {
public:
    // Helper function to calculate the sum of ceil(a[i] / divisor) for all elements
    int getTotalDividedSum(const vector<int>& nums, int divisor) {
        int total = 0;
        for (int num : nums) {
            // Equivalent to ceil(num / divisor) using integer math
            // total += (num + divisor - 1) / divisor;
            //       or
            total += (num / divisor) + ( num % divisor != 0);
        }
        return total;
    }

    // Main function to find the smallest divisor such that the sum of ceilings <= threshold
    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = 1e6;
        int optimalDivisor = 1; // Default if all fail, although it will be updated

        // Binary search for smallest valid divisor
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (getTotalDividedSum(nums, mid) <= threshold)
            {
                // Valid divisor → try to minimize it
                optimalDivisor = mid;
                high = mid - 1;
            }
            else
            {
                // Too large of a sum → need a bigger divisor to reduce quotient values
                low = mid + 1;
            }
        }

        return optimalDivisor;
    }
};
