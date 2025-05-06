class Solution {
public:
    // Check if it's possible to divide all elements in 'nums'
    // into at most 'maxOperations' operations with maximum size 'maxSize'
    bool isPossible(int maxSize, vector<int>& nums, int maxOperations) {
        for (int i = 0; i < nums.size(); i++) {
            // Calculate how many operations are needed for nums[i]
            maxOperations -= (nums[i] / maxSize);
            // If it's perfectly divisible, one extra op was counted, subtract it
            if (nums[i] % maxSize == 0) maxOperations++;
        }
        return maxOperations >= 0;
    }

    // Find the minimum possible max size of a bag after performing at most 'maxOperations'
    int minimumSize(vector<int>& nums, int maxOperations) {
        int low = 1, high = INT_MAX;
        int result = 0;

        // Binary search to find the smallest valid maximum size
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isPossible(mid, nums, maxOperations)) {
                result = mid;        // Valid, try to minimize further
                high = mid - 1;
            } else {
                low = mid + 1;       // Too small, need larger size
            }
        }
        return result;
    }
};
