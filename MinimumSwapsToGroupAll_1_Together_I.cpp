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
        for (int num : nums)
        {
            totalOnes += (num == 1);
        }

        int windowSize = totalOnes;      // Size of sliding window
        int onesInWindow = 0;            // Count of 1's in current window
        int maxOnes = 0;                 // Maximum 1's in any window

        // Step 2: Initialize first window
        for (int i = 0; i < windowSize; i++)
        {
            onesInWindow += (nums[i] == 1);
        }
        maxOnes = onesInWindow;

        // Step 3: Slide the window
        for (int i = windowSize; i < n; i++)
        {
            onesInWindow -= (nums[i - windowSize] == 1);  // remove left element
            onesInWindow += (nums[i] == 1);               // add right element
            maxOnes = max(maxOnes, onesInWindow);
        }

        // Minimum swaps = total 1's - max 1's in a window
        return windowSize - maxOnes;
    }
};

/*
APPROACH:

1. Count total number of 1's in the array.
2. Use sliding window of size equal to total 1's.
3. Count 1's in each window and track maximum.
4. Minimum swaps = total 1's - maximum 1's in any window.

Time Complexity:  O(n)  -> single pass to count + single sliding window pass
Space Complexity: O(1)  -> only a few integer variables used
*/
