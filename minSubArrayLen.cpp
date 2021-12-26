class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int l = 0, r = 0, n = nums.size(), sum = 0, len = INT_MAX;
        while (r < n) {
            sum += nums[r];
            while (sum >= s) {
                len = min(len, r - l +1);
                sum -= nums[l];
                l++;
            }
            r++;
        }
        return len == INT_MAX ? 0 : len;
    }
};

// this question contain only +ve that is why.
