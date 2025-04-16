/*
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long maxSum = 0;             // Stores the maximum sum of valid subarrays
        long long currentSum = 0;         // Current sliding window sum
        unordered_map<int, int> freqMap;  // Frequency map to track element counts in the window
        int index = 0;

        // Initialize the first window of size 'k'
        while (index < k && index < nums.size()) {
            freqMap[nums[index]]++;
            currentSum += nums[index];
            index++;
        }

        // If the first window has all unique elements, update maxSum
        if (freqMap.size() == k)
            maxSum = currentSum;

        // Slide the window across the rest of the array
        while (index < nums.size()) {
            // Add new element to the window
            freqMap[nums[index]]++;
            currentSum += nums[index];

            // Remove the element that slides out of the window
            freqMap[nums[index - k]]--;
            if (freqMap[nums[index - k]] == 0) {
                freqMap.erase(nums[index - k]); // Clean up the map
            }
            currentSum -= nums[index - k];

            // If current window has all unique elements, check if it's the max sum
            if (freqMap.size() == k) {
                maxSum = max(maxSum, currentSum);
            }

            index++;
        }

        return maxSum;
    }
};
*/

// we can solve using map just like above, but as the array element <=10^5 , so we can use array intead of map

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        const int MAX_VAL = 1e5 + 1;
        vector<int> freq(MAX_VAL, 0);
        long long currentSum = 0, maxSum = 0;
        int countUnique = 0;

        // Phase 1: Process first window of size k
        for (int i = 0; i < k && i < nums.size(); ++i) {
            currentSum += nums[i];
            if (freq[nums[i]] == 0) 
                countUnique++;
            freq[nums[i]]++;
        }

        if (countUnique == k)
            maxSum = currentSum;

        // Phase 2: Slide the window
        for (int i = k; i < nums.size(); ++i) {
            // Remove element going out
            currentSum -= nums[i - k];
            freq[nums[i - k]]--;
            if (freq[nums[i - k]] == 0)
                 countUnique--;

            // Add new element coming in
            currentSum += nums[i];
            if (freq[nums[i]] == 0) 
                countUnique++;
            freq[nums[i]]++;

            if (countUnique == k)
                maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};
