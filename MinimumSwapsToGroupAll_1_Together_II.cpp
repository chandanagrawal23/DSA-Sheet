#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    int minSwaps(vector<int>& nums) 
    {
        int n = nums.size();

        // Step 1: Count total number of 1's
        int totalOnes = 0;
        for (int num : nums) totalOnes += (num == 1);
        if (totalOnes == 0) return 0; // No 1's, no swaps needed

        // Step 2: Sliding window of size totalOnes over circular array
        int onesInWindow = 0, maxOnes = 0;

        // Initialize first window (first totalOnes elements)
        for (int i = 0; i < totalOnes; i++)
        {
            onesInWindow += nums[i];
        }
        maxOnes = onesInWindow;

        // Slide window over circular array (means total elemeny + at max 1 circular array)
        for (int i = totalOnes; i < n + totalOnes; i++)
        {
            onesInWindow += nums[i % n];            // Add new element (wrap around)
            onesInWindow -= nums[(i - totalOnes) % n]; // Remove left element
            maxOnes = max(maxOnes, onesInWindow);
        }

        // Minimum swaps = total 1's - maximum 1's in any window
        return totalOnes - maxOnes;
    }
};

/*
APPROACH:

1. Count total number of 1's in the array -> this is window size.
2. Treat array as circular: slide window of size totalOnes over 2*n elements (wrap using modulo).
3. Track maximum 1's in any window.
4. Minimum swaps = total 1's - max 1's in any window.

Time Complexity:  O(n)  -> single pass over circular array
Space Complexity: O(1)  -> only counters used
*/
