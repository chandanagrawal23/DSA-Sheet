class Solution 
{
public:
    int minimumSubarrayLength(vector<int>& a, int k) 
    {
        int ans = INT_MAX;
        int n = a.size();

        // Try every subarray starting from index i
        for (int i = 0; i < n; i++) 
        {
            int x = 0;  // bitwise OR accumulator

            // Expand the subarray from i to j
            for (int j = i; j < n; j++) 
            {
                x |= a[j];  // OR current element to the result

                // If OR becomes >= k, check and update minimum length
                if (x >= k) 
                {
                    ans = min(ans, j - i + 1);
                }
            }
        }

        // If no such subarray found
        if (ans == INT_MAX) 
        {
            return -1;
        }

        return ans;
    }
};

/*
Approach:

- We check all subarrays starting from each index `i`.
- For each subarray, we maintain a bitwise OR (`x`) of its elements.
- As soon as `x >= k`, we calculate the subarray length (`j - i + 1`) and update the minimum.
- Finally, return the minimum length found or -1 if no subarray satisfies the condition.

Time Complexity: O(n^2) — two nested loops over the array.
Space Complexity: O(1) — no extra space used.
*/
