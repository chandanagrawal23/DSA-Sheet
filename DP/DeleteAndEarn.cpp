class Solution {
public:
    // Recursive DP with memoization
    int solve(vector<int> &freq, int i, int n, vector<int> &dp) {
        if (i >= n)
            return 0;

        if (dp[i] != -1)
            return dp[i];

        // Option 1: Pick current number => earn i * freq[i] + solve from i + 2
        int pickCurrent = i * freq[i] + solve(freq, i + 2, n, dp);

        // Option 2: Skip current number => move to i + 1
        int skipCurrent = solve(freq, i + 1, n, dp);

        return dp[i] = max(pickCurrent, skipCurrent);
    }

    int deleteAndEarn(vector<int>& nums) {
        vector<int> freq(1e4 + 10, 0);  // Frequency array

        for (int val : nums) {
            freq[val]++;
        }

        vector<int> dp(freq.size(), -1);  // Memoization table
        return solve(freq, 0, freq.size(), dp);
    }
};

/*
Approach:
- Convert the problem into a variation of "House Robber".
- Build a frequency array: freq[i] = count of i in nums.
- At each index i:( which denotes number)
    - pickCurrent = i * freq[i] + solve(i + 2)
    - skipCurrent = solve(i + 1)
- Return max(pickCurrent, skipCurrent) using top-down DP.

Time Complexity: O(N), where N = 10^4
Space Complexity: O(N), for freq and dp arrays

*/
