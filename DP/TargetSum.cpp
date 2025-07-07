class Solution 
{
public:
    int findTargetSumWays(vector<int>& nums, int target) 
    {
        int n = nums.size();
        int offset = 1000; // To shift possible negative sums to 0-based index
        vector<vector<int>> dp(n, vector<int>(2001, -1)); // dp[i][sum + offset]

        return recursion(nums, 0, 0, target, dp, offset);
    }

private:
    int recursion(vector<int>& nums, int index, int sum, int target, vector<vector<int>>& dp, int offset)
    {
        if (index == nums.size())
        {
            return (sum == target) ? 1 : 0; // One valid way if target reached
        }

        if (dp[index][sum + offset] != -1)
        {
            return dp[index][sum + offset]; // Return cached result
        }

        // Option 1: Add current number
        int plus = recursion(nums, index + 1, sum + nums[index], target, dp, offset);

        // Option 2: Subtract current number
        int minus = recursion(nums, index + 1, sum - nums[index], target, dp, offset);

        // Cache and return total ways
        return dp[index][sum + offset] = plus + minus;
    }
};

/*
Approach:
- At each index, we choose to add or subtract the current number.
- Use recursion with memoization to cache results: dp[index][sum].
- We shift `sum` by an offset (1000) to avoid negative indices.

Time Complexity: O(n * 2001) = O(n * T) where T is max sum range (−1000 to +1000)
Space Complexity: O(n * T) for memo table
*/
