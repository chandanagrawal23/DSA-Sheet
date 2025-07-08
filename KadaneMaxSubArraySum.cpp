// 1. Find only max subarray sum

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySum(vector<int> &arr) {
    
    // Stores the result (maximum sum found so far)
    int res = arr[0];           
    
    // Maximum sum of subarray ending at current position
    int maxEnding = arr[0];     

    for (int i = 1; i < arr.size(); i++) {
        
        // Either extend the previous subarray or start 
        // new from current element
        maxEnding = max(arr[i], maxEnding + arr[i]);

        // Update result if the new subarray sum is larger
        res = max(res, maxEnding);
    }
    return res;
}

int main() {
    vector<int> arr = {2, 3, -8, 7, -1, 2, 3};
    cout << maxSubarraySum(arr); 
    return 0;
}

// =========================================================================================================================

// 2. Find Max Subarray Sum with start and ending index of that subarray too.

#include <iostream>
#include <vector>
using namespace std;

// Kadane's Algorithm to find max subarray sum along with indices
int kadane_maxSubarraySum(const vector<int> &arr, int &start, int &end)
{
    int maxSum = arr[0], currSum = arr[0];
    start = end = 0;        // Initialize result indices
    int tempStart = 0;      // Temporary start index

    for (int i = 1; i < arr.size(); ++i)
    {
        // Decide whether to extend the previous subarray or start new
        if (arr[i] > currSum + arr[i])
        {
            currSum = arr[i];
            tempStart = i;  // Start new subarray here
        }
        else
        {
            currSum += arr[i];
        }

        // Update maxSum and record indices if needed
        if (currSum > maxSum)
        {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }
    }
    return maxSum;
}

int main()
{
    vector<int> arr = {2, 3, -8, 7, -1, 2, 3};
    int start, end;

    int maxSum = kadane_maxSubarraySum(arr, start, end);

    cout << "Max Sum: " << maxSum << "\nIndices: [" << start << ", " << end << "]\nSubarray: ";
    for (int i = start; i <= end; ++i)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
