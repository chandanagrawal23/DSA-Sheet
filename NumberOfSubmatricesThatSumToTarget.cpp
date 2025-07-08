#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:

    /////////////// APPROACH 1: Brute Force (Row compression + nested loops) ////////////////////////
    
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) 
    {
        int n = matrix.size(), m = matrix[0].size();
        int count = 0;

        // Fix the left column
        for (int left = 0; left < m; ++left) 
        {
            vector<int> rowSum(n, 0);  // compressed 1D array between [left, right]

            // Fix the right column
            for (int right = left; right < m; ++right) 
            {
                // Build the 1D sum for current column range
                for (int i = 0; i < n; ++i) 
                {
                    rowSum[i] += matrix[i][right];
                }

                // Count subarrays in rowSum[] with sum == target
                for (int i = 0; i < n; ++i) 
                {
                    int sum = 0;
                    for (int j = i; j < n; ++j) 
                    {
                        sum += rowSum[j];
                        if (sum == target)
                            count++;
                    }
                }
            }
        }

        return count;
    }



    /////////////// APPROACH 2: Optimized using Prefix Sum + Hash Map ////////////////////////

    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int count = 0;

        // Fix left column
        for (int left = 0; left < m; ++left)
        {
            vector<int> rowSum(n, 0); // Temporary 1D array to store row sums

            // Expand to right column
            for (int right = left; right < m; ++right)
            {
                for (int i = 0; i < n; ++i)
                {
                    rowSum[i] += matrix[i][right]; // Build cumulative row sum
                }

                // Use prefix sum + map to count subarrays with sum = target
                unordered_map<int, int> freq;
                int prefix = 0;

                for (int i = 0; i < n; ++i)
                {
                    prefix += rowSum[i];

                    // Subarray from start till i has sum == target
                    if (prefix == target)
                        count++;

                    // Check if there exists a prefix sum such that
                    // current prefix - previous prefix == target
                    if (freq.find(prefix - target) != freq.end())
                    {
                        count += freq[prefix - target];
                    }

                    // Update frequency map
                    freq[prefix]++;
                }
            }
        }

        return count;
    }
};

/*

APPROACH 1: Brute Force using Row Compression + Nested Loop
-----------------------------------------------------------
- Fix two columns `left` and `right`.
- Compress the submatrix between those columns into a 1D array of row sums.
- For that 1D array, check every subarray sum using two nested loops.
- Count the ones which match the target.

Time: O(m² * n²)
Space: O(n)

Works well in practice due to linear memory access and no hashmap overhead.

-----------------------------------------------------------

APPROACH 2: Optimized with Prefix Sum + HashMap
-----------------------------------------------------------
- Same first step: Fix two columns `left` and `right`.
- Build compressed rowSum[] of n elements.
- Instead of brute-forcing subarrays, use prefix sum and a hashmap to track how many times each prefix has occurred.
- If (prefixSum - target) exists in map, increment count by that frequency.

Time: O(m² * n)
Space: O(n)

This is optimal in theory and handles large matrices efficiently.

*/
