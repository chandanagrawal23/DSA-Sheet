/*
// same question just Partition Array To Minimize Sum Of Minimums : https://www.geeksforgeeks.org/dsa/divide-the-array-in-k-segments-such-that-the-sum-of-minimums-is-maximized/
Here we are doing for MAX


Problem Statement:

You are given an array of integers representing the complexity of tasks, and an integer k representing the number of days available to complete all tasks. 

You must partition the array into exactly k contiguous subarrays, each representing the tasks done on a particular day.

The complexity for each day is the maximum complexity value among the tasks assigned to that day.

Your goal is to minimize the sum of these maximum daily complexities over all k days.

Input:
- complexity: List of integers of length n representing task complexities.
- k: Number of days (partitions).

Output:
- The minimum possible sum of the maximum complexities of the k partitions.
- Return -1 if it is not possible to partition the array into k subarrays.

Constraints:
- 1 <= n <= 500
- 1 <= complexity[i] <= 10^9
- 1 <= k <= n

Example 1:
Input: complexity = [30, 10, 40, 20, 50], k = 2
Output: 80

Explanation:
- Partition as [30, 10] and [40, 20, 50]
- Max complexities are 30 and 50 respectively
- Sum = 30 + 50 = 80 (minimum possible)

Example 2:
Input: complexity = [5, 1, 1, 1, 5], k = 3
Output: 11

Explanation:
- Partition as [5], [1, 1, 1], and [5]
- Max complexities are 5, 1, and 5 respectively
- Sum = 5 + 1 + 5 = 11
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution
{
    // Recursive function to find minimum sum of max partitions
    int solve(int start, int k, int n, const vector<int> &arr, vector<vector<int>> &memo)
    {
        if (start == n && k == 0)
        {
            return 0; // All partitions done successfully
        }
        if (start == n || k == 0)
        {
            return INT_MAX; // Invalid partitioning scenario
        }

        if (memo[start][k] != -1)
        {
            return memo[start][k]; // Return cached result
        }

        int currentMax = INT_MIN;
        int answer = INT_MAX;

        for (int end = start; end < n; end++)
        {
            currentMax = max(currentMax, arr[end]); // Update max for current partition

            int next = solve(end + 1, k - 1, n, arr, memo); // Recurse for next partitions
            if (next != INT_MAX)
            {
                answer = min(answer, currentMax + next); // Choose minimum sum
            }
        }

        memo[start][k] = answer; // Cache result
        return answer;
    }

public:
    int findMinSumOfMaxPartitions(const vector<int> &complexity, int k)
    {
        int n = complexity.size();
        vector<vector<int>> memo(n + 1, vector<int>(k + 1, -1)); // Memoization table
        int res = solve(0, k, n, complexity, memo);
        return res == INT_MAX ? -1 : res;
    }
};

int main()
{
    Solution sol1;
    vector<int> tc1 = {30, 10, 40, 20, 50};
    int k1 = 2;
    cout << "Test Case 1 result: " << sol1.findMinSumOfMaxPartitions(tc1, k1) << "\n";

    Solution sol2;
    vector<int> tc2 = {5, 1, 1, 1, 5};
    int k2 = 3;
    cout << "Test Case 2 result: " << sol2.findMinSumOfMaxPartitions(tc2, k2) << "\n";

    return 0;
}

/*
Approach:
- Use recursion with memoization (top-down DP) to explore all ways to partition the array into k contiguous subarrays.
- For each partition starting at index 'start', expand the partition end index and track the maximum value in that subarray.
- Recursively solve for the remaining array and partitions.
- Use memoization to avoid repeated calculations.

Time Complexity:
- O(n^2 * k), since for each start and k, we iterate over possible end indices up to n.

Space Complexity:
- O(n * k) for memoization table and O(n) recursion stack in worst case.
*/
