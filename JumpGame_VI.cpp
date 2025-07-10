class Solution
{
public:
    int maxResult(vector<int>& nums, int k)
    {
        int n = nums.size();
        deque<int> dq;         // Stores indices in decreasing order of score
        vector<int> dp(n);     // dp[i] = max score to reach index i
        dp[n - 1] = nums[n - 1];
        dq.push_back(n - 1);

        for (int i = n - 2; i >= 0; --i)
        {
            // Remove indices out of the jump range
            while (!dq.empty() && dq.front() > i + k)
            {
                dq.pop_front();
            }

            // dp[i] = nums[i] + best dp[j] where j in [i+1, i+k]
            dp[i] = nums[i] + dp[dq.front()];

            // Maintain monotonic decreasing deque
            while (!dq.empty() && dp[i] >= dp[dq.back()])
            {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        return dp[0];
    }
};

/*
Approach:
---------
- We want to reach the last index with max total score.
- At each index `i`, we can jump to any index j in range [i+1, i+k].
- dp[i] = nums[i] + max(dp[i+1], ..., dp[i+k])
- Use a monotonic deque to maintain max values in the sliding window of size `k`.

Key Optimizations:
- Use a deque to keep track of indices of max dp values in the window.
- Remove any indices from deque that are out of jump range or smaller than current score.

Time Complexity: O(n)
- Each index is pushed and popped from the deque at most once.

Space Complexity: O(n)
- For the dp array and deque (can be reduced to O(k) if done in-place).
*/
