class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;  // To store valid combinations
        vector<int> comb;         // Current combination
        vector<int> nums;
        
        for (int i = 1; i <= 9; i++) nums.push_back(i);  // Numbers from 1 to 9
        
        backtrack(nums, n, comb, res, 0, k);
        return res;
    }

    void backtrack(vector<int>& nums, int target, vector<int>& comb, vector<vector<int>>& res, int idx, int k) {
        if (target == 0 && comb.size() == k) {
            res.push_back(comb);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            if (target >= nums[i]) {
                comb.push_back(nums[i]);
                backtrack(nums, target - nums[i], comb, res, i + 1, k);
                comb.pop_back();
            } else {
                break;
            }
        }
    }
};
