// 1. This is to check whether a subarray exist whose sum is K

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to check if subarray with sum == k exists
bool hasSubarrayWithSumK(const vector<int> &arr, int k)
{
    unordered_map<int, int> prefixSumMap;  // prefixSum → first index
    int sum = 0;

    for (int i = 0; i < arr.size(); ++i)
    {
        sum += arr[i];  // Compute prefix sum up to current index

        if (sum == k)
        {
            return true; // Subarray from 0 to i has sum k
        }

        if (prefixSumMap.count(sum - k))
        {
            return true; // Subarray between (prefixSumMap[sum-k]+1) to i has sum k
        }

        prefixSumMap[sum] = i;  // Store current prefix sum with index
    }

    return false; // No subarray with sum k found
}

int main()
{
    vector<pair<vector<int>, int>> testCases = {
        {{1, 4, -2, -2, 5, -4, 3}, 5},   // ✅ Has subarray with sum 5
        {{3, 1, 0, -1, 2}, 3},          // ✅ Has subarray with sum 3
        {{5, 1, 2, 6, 9}, 100}          // ❌ No subarray with sum 100
    };

    for (int i = 0; i < testCases.size(); ++i)
    {
        cout << "Test Case " << i + 1 << ": ";
        if (hasSubarrayWithSumK(testCases[i].first, testCases[i].second))
        {
            cout << "Subarray with sum " << testCases[i].second << " exists\n";
        }
        else
        {
            cout << "No subarray with sum " << testCases[i].second << "\n";
        }
    }

    return 0;
}

/*

🔍 Approach: Prefix Sum + Hash Map

- Maintain a running sum (prefix sum) while iterating the array.
- At each step, check:
    1. If sum == k → subarray from index 0 to i has sum k.
    2. If (sum - k) is found in the map → there exists a previous prefix sum,
       such that the elements between those two indices sum to k.

📌 Why does (sum - k) in map mean subarray sum = k?
    Let’s say:
        prefixSum[j] = sum
        prefixSum[i] = sum - k
    Then: sum(i+1 to j) = prefixSum[j] - prefixSum[i] = k

💡 Detailed Example:
    arr = {1, 4, -2, -2, 5, -4, 3}, k = 5

    Prefix sums:
    - Index 0 → sum = 1
    - Index 1 → sum = 5 ✅ sum == k → subarray [1, 4]
    - Index 2 → sum = 3
    - Index 3 → sum = 1
    - Index 4 → sum = 6 → sum - k = 1 found in map ✅ → subarray [5] (from index 4)
    - Index 5 → sum = 2
    - Index 6 → sum = 5 ✅ again sum == k → subarray [1,4,-2,-2,5,-4,3]

✅ So, subarrays with sum = 5 exist

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)

*/


///=============================================================================================================================

// 2. Count subarrays whose sum is K

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to count number of subarrays with sum equal to k
int countSubarraysWithSumK(vector<int>& nums, int k)
{
    unordered_map<int, int> prefixFreq;  // Stores frequency of prefix sums
    int count = 0, prefixSum = 0;

    for (int num : nums)
    {
        prefixSum += num;  // Running sum up to current index

        if (prefixSum == k)
        {
            ++count;  // Subarray from 0 to current index has sum k
        }

        // Check how many times (prefixSum - k) has occurred
        if (prefixFreq.count(prefixSum - k))
        {
            count += prefixFreq[prefixSum - k];
        }

        ++prefixFreq[prefixSum];  // Increment frequency of current prefix sum
    }

    return count;
}

int main()
{
    vector<int> arr = {1, 2, 3, -2, 5};
    int k = 5;

    cout << "Count of subarrays with sum " << k << ": "
         << countSubarraysWithSumK(arr, k) << endl;

    return 0;
}

/*

🔍 Approach:
- Use prefix sum and a hash map to store how many times each prefix sum has occurred.
- For each index, check if there’s a previous prefix such that (prefixSum - k) exists.
- If yes, it means the subarray between that previous index and current one sums to k.
- Add the frequency of (prefixSum - k) to the total count.

📌 Why?
    prefixSum[j] - prefixSum[i] == k ⇒ subarray (i+1 to j) has sum k

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)

*/

