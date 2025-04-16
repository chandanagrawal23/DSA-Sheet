class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        int n = nums.size();
        std::map<int, int> freq;     // Frequency map to count occurrences of each number
        long long total = 0;
        int countPairs = 0;          // Total number of valid pairs in the current window
        int i = 0;
        long long invalidSubarrays = 0;

        // Two-pointer sliding window
        for (int j = 0; j < n; j++) {
            // For each new element nums[j], we add the number of pairs it forms
            countPairs += freq[nums[j]];
            freq[nums[j]]++;

            // Shrink the window from the left until the number of pairs < k
            while (countPairs >= k) {
                // Remove the effect of nums[i] from pair count
                // (freq[nums[i]] - 1) is how many elements nums[i] was forming pairs with
                countPairs -= (freq[nums[i]] - 1);  // ⚠️ Most important step
                freq[nums[i]]--;
                i++;
            }

            // All subarrays ending at j and starting from i to j are invalid (do not satisfy condition)
            invalidSubarrays += 1LL * (j - i + 1);
        }

        // Total number of subarrays is n*(n+1)/2
        long long totalSubarrays = 1LL * n * (n + 1) / 2;

        // Valid (good) subarrays = total - invalid
        return totalSubarrays - invalidSubarrays;
    }
};
