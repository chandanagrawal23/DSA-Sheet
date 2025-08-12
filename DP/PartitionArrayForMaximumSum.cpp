// In this solution we will use "FOR" loop
#include <bits/stdc++.h>
using namespace std;

class Solution
{
    // Recursive function to find max sum of max elements in partitions from index 'start'
    int recur(int start, int maxPartitionSize, int length, const vector<int> &tasks, vector<int> &dp)
    {
        if (start == length)
            return 0; // All elements partitioned successfully

        if (dp[start] != -1)
            return dp[start]; // Return dpd result

        int maxTaskComplexity = 0;
        int maxSum = 0;

        // Expand current partition up to maxPartitionSize
        for (int end = start; end < min(length, start + maxPartitionSize); ++end)
        {
            maxTaskComplexity = max(maxTaskComplexity, tasks[end]);  // Track max in current partition

            // Recur for remaining tasks after this partition
            int nextSum = recur(end + 1, maxPartitionSize, length, tasks, dp);

            // Update maxSum with best partitioning result
            maxSum = max(maxSum, maxTaskComplexity * (end - start + 1) + nextSum);
        }

        return dp[start] = maxSum; // Memoize and return
    }

public:
    int maxSumAfterPartitioning(const vector<int> &tasks, int maxPartitionSize)
    {
        int length = tasks.size();
        vector<int> dp(length, -1);  // Memo table to store results for subproblems
        return recur(0, maxPartitionSize, length, tasks, dp);
    }
};

int main()
{
    Solution solver;

    vector<int> testCase1 = {1, 15, 7, 9, 2, 5, 10};
    int k1 = 3;
    cout << "Test Case 1 result: " << solver.maxSumAfterPartitioning(testCase1, k1) << "\n";

    vector<int> testCase2 = {1, 2, 3, 4, 5};
    int k2 = 2;
    cout << "Test Case 2 result: " << solver.maxSumAfterPartitioning(testCase2, k2) << "\n";

    return 0;
}

/*
Approach:
- Use recursion with memoization to partition array into contiguous subarrays of max length 'k'.
- For each starting index, try all subarrays up to length 'k'.
- Track the max element in the current subarray.
- Recursively find max sum for the rest of the array.
- Memoize results to avoid recomputation.

Time Complexity:
- O(n * k), where n = number of elements and k = max partition size.

Space Complexity:
- O(n) for memoization array and recursion call stack.
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

