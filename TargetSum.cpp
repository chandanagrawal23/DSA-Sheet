class Solution {
public:
    // Declare a 2D dp array to store the results of subproblems
    int dp[100][2500];

    // Main function to find the number of ways to reach the target sum
    int findTargetSumWays(vector<int>& nums, int target) {
        // Initialize the count variable to 0
        int cnt = 0;
        
        // Set the dp array to -1, indicating unvisited states
        memset(dp, -1, sizeof(dp));
        
        // Start the recursion from the 0th index and 0 as the initial total
        return recursion(nums, 0, 0, target, nums.size(), cnt);
    }

    // Recursive function to calculate the number of ways to reach the target sum
    int recursion(vector<int>& nums, int start, int total, int target, int n, int &cnt) {
        // Base case: If we have processed all elements
        if (start == n) {
            // If the total equals the target, return 1 (valid way)
            // Otherwise, return 0 (no valid way)
            return (total == target);
        }

        // If the result for this state has already been computed, return the stored value
        if (dp[start][total + 1000] != -1) {
            return dp[start][total + 1000];
        }

        // Recurse with the current element being added to the total (plus sign)
        int usePlusSign = recursion(nums, start + 1, total + nums[start], target, n, cnt);
        
        // Recurse with the current element being subtracted from the total (minus sign)
        int useMinusSign = recursion(nums, start + 1, total - nums[start], target, n, cnt);
        
        // The total number of ways is the sum of the two possibilities
        int totalSum = usePlusSign + useMinusSign;

        // Store the result for this state in the dp array
        dp[start][total + 1000] = totalSum;

        // Return the result
        return dp[start][total + 1000];
    }
};
