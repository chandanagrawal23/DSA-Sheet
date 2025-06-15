#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();
        if (n == 1) return 1LL * nums[0] * nums[0];

        vector<int> maxSuffix(n), minSuffix(n);
        maxSuffix[n - 1] = nums[n - 1];
        minSuffix[n - 1] = nums[n - 1];

        // Precompute max and min suffix values from each index to the end
        for (int i = n - 2; i >= 0; --i) {
            maxSuffix[i] = max(maxSuffix[i + 1], nums[i]);
            minSuffix[i] = min(minSuffix[i + 1], nums[i]);
        }

        long long maxProduct = LLONG_MIN;

        // Try each position as the start of m-length subarray
        for (int i = 0; i <= n - m; ++i) {
            long long prodWithMax = 1LL * nums[i] * maxSuffix[i + m - 1];
            long long prodWithMin = 1LL * nums[i] * minSuffix[i + m - 1];
            maxProduct = max({maxProduct, prodWithMax, prodWithMin});
        }

        return maxProduct;
    }
};

/*
🔹 Approach Summary:
- For each position i, fix nums[i] as one element of the product.
- Find the maximum and minimum in the suffix starting from index (i + m - 1).
- Calculate both products and take the maximum across all valid positions.
- Precompute suffix max/min arrays for O(1) access and avoid TLE.
- Time complexity: O(n)
*/
