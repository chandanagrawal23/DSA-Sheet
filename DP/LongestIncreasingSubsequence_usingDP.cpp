// Top-down DP, with Memoization ,  2D DP
class Solution {
public:
    int solve(int i, int prev, vector<int> &a, vector<vector<int>> &dp)
    {
        if (i == a.size())
            return 0;

        if (dp[i][prev + 1] != -1)
            return dp[i][prev + 1];  // already computed

        int take = 0;
        // if this is first time we are taking, or the current element is greater than previous element
        if (prev == -1 || a[i] > a[prev])
        {
            take = 1 + solve(i + 1, i, a, dp);  // include current element
        }

        int skip = solve(i + 1, prev, a, dp);  // exclude current element

        return dp[i][prev + 1] = max(take, skip);
    }

    int lengthOfLIS(vector<int> &a)
    {
        int n = a.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));  // dp[i][prev+1] = LIS starting at i with last index prev
        return solve(0, -1, a, dp);
    }
};

/*
Approach:
- At every index, we decide whether to include the element in LIS or skip it.
- We track the previous index to ensure increasing order.
- Use 2D DP where dp[i][prev+1] stores the LIS starting from i with last included index = prev.

Time Complexity: O(N^2)
Space Complexity: O(N^2)
*/


//=====================================================================================================================================

// Bottom-Up DP , Iterative DP ,  1D DP

class Solution {
public:
    int lengthOfLIS(vector<int>& a)
    {
        int n = a.size();
        vector<int> dp(n, 1);  // dp[current] = length of LIS ending at current index

        for (int current = 1; current < n; current++)
        {
            for (int previous = 0; previous < current; previous++)
            {
                if (a[current] > a[previous])
                {
                    dp[current] = max(dp[current], dp[previous] + 1);  // extend LIS ending at previous
                }
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};
/*
Approach:
- dp[i] stores the length of the longest increasing subsequence ending at index i.
- For each i, look at all j < i, and if a[i] > a[j], try to extend the LIS ending at j.
- Final answer is the maximum of all dp[i].

Time Complexity: O(N^2)
Space Complexity: O(N)
*/

