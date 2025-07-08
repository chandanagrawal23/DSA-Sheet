#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to find length of longest subarray with sum == k
int longestSubarrayWithSumK(vector<int>& nums, int k)
{
    unordered_map<int, int> prefixIndex;  // Stores first occurrence of prefix sum
    int prefixSum = 0, maxLen = 0;

    for (int i = 0; i < nums.size(); ++i)
    {
        prefixSum += nums[i];  // Running sum

        if (prefixSum == k)
        {
            maxLen = i + 1;  // Subarray from index 0 to i
        }

        // If (prefixSum - k) seen before, update maxLen
        if (prefixIndex.count(prefixSum - k))
        {
            int len = i - prefixIndex[prefixSum - k];
            maxLen = max(maxLen, len);
        }

        // Store first occurrence of each prefix sum
        if (!prefixIndex.count(prefixSum))
        {
            prefixIndex[prefixSum] = i;
        }
    }

    return maxLen;
}

int main()
{
    vector<int> arr = {1, 2, 3, -2, 5, 1};
    int k = 5;

    cout << "Length of longest subarray with sum " << k << ": "
         << longestSubarrayWithSumK(arr, k) << endl;

    return 0;
}

/*

🔍 Approach:
- Maintain prefix sum while iterating.
- Store the first index where each prefix sum appears.
- If prefixSum == k, then subarray from start to i is valid.
- If (prefixSum - k) was seen earlier, then subarray between that index+1 and current index sums to k.
- Track the max length of such subarrays.

📌 Example:
    arr = {1, 2, 3, -2, 5, 1}, k = 5
    Longest subarrays: {2,3}, {3,-2,5}, {5}, all have length ≤ 3

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)

*/
