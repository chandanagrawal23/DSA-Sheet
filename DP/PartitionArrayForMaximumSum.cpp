// In this solution we will use "FOR" loop
class Solution {
public:
    // Recursive DP to find maximum sum after partitioning
    int solve(vector<int> &a, int i, int n, int k, vector<int> &dp)
    {
        if (i >= n)
            return 0;

        if (dp[i] != -1)
            return dp[i];

        int maxVal = -1;
        int currMax = -1;

        for (int j = i; j < min(i + k, n); j++)
        {
            currMax = max(currMax, a[j]);              // track max in current partition
            int partSum = currMax * (j - i + 1);       // value of current partition
            int remSum = solve(a, j + 1, n, k, dp);    // solve for remaining array
            maxVal = max(maxVal, partSum + remSum);    // take maximum of all options
        }

        return dp[i] = maxVal;
    }

    int maxSumAfterPartitioning(vector<int> &a, int k)
    {
        int n = a.size();
        vector<int> dp(n, -1);
        return solve(a, 0, n, k, dp);
    }
};

/*
Approach:
- At each index, try partitions of size 1 to k.
- Track maximum in current partition and calculate total sum for that cut.
- Recursively solve for the rest of the array and memoize.

Time Complexity: O(N * K), where N = array size, K = max partition size
Space Complexity: O(N), for memoization array
*/



//=======================================================================================================================================================


// In this solution we will "not use FOR" loop

class Solution {
public:
    int solve(vector<int> &a, int i, int n, int currMax, int len, int k, vector<int> &dp)
    {
        if (i == n)
            return currMax * len; // finish last partition

        if (dp[i - len] != -1)
            return dp[i - len];

        int extend = INT_MIN;
        int closeAndStartNew = INT_MIN;

        // Option 1: Extend current partition
        if (len < k)
        {
            extend = solve(a, i + 1, n, max(currMax, a[i]), len + 1, k, dp);
        }

        // Option 2: Close current partition, start new
        int partSum = currMax * len;
        closeAndStartNew = partSum + solve(a, i + 1, n, a[i], 1, k, dp);

        return dp[i - len] = max(extend, closeAndStartNew);
    }

    int maxSumAfterPartitioning(vector<int> &a, int k)
    {
        int n = a.size();
        vector<int> dp(n, -1);
        return solve(a, 1, n, a[0], 1, k, dp);  // start from index 1 with first element
    }
};

/*
Approach:
- Simulate partitioning without a for-loop.
- At each step:
    1. Extend current partition (if length < k)
    2. Close partition and solve rest from next index
- Memoize using starting index of current partition (i - len)

Time Complexity: O(N * K)
Space Complexity: O(N), for memoization
*/

