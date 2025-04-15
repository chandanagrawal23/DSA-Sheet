class Solution {
public:
    int countArrangement(int n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; i++) {
            nums[i] = i + 1;  // Initialize nums with 1 to n
        }
        int result = 0;
        generatePermutations(nums, n, 0, result);  // Start permutation generation
        return result;
    }

    void generatePermutations(vector<int>& nums, int n, int idx, int & result) {
        if (idx == n) {
            result++;  // Valid permutation found
            return;
        }
        for (int i = idx; i < n; i++) {
            swap(nums[i], nums[idx]);  // Swap to generate new permutation
            // Check if the arrangement is valid
            if (nums[idx] % (idx + 1) == 0 || (idx + 1) % nums[idx] == 0) {
                generatePermutations(nums, n, idx + 1, result);  // Recurse for next index
            }
            swap(nums[i], nums[idx]);  // Backtrack
        }
    }
};
