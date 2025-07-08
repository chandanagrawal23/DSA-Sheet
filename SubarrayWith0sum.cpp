#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to check if subarray with 0 sum exists
bool hasZeroSumSubarray(const vector<int> &arr)
{
    unordered_set<int> prefixSums; // To store prefix sums seen so far
    int sum = 0;

    for (int num : arr)
    {
        sum += num;                      // Compute running prefix sum

       // if sum is 0 , or the sum is already seen, that means from the last occurence index +1 to current index sum is 0 
        if (sum == 0 || prefixSums.count(sum))
        {
            return true;                // Found 0 sum subarray
        }

        prefixSums.insert(sum);         // Store current sum
    }

    return false;
}

int main()
{
    vector<vector<int>> testCases = {
        {1, 4, -2, -2, 5, -4, 3},   // ✅ Has subarray with 0 sum
        {3, 2, -3, -2, 1},          // ✅ Has subarray with 0 sum
        {5, 1, 2, 6, 9}             // ❌ No subarray with 0 sum
    };

    for (int i = 0; i < testCases.size(); ++i)
    {
        cout << "Test Case " << i + 1 << ": ";
        if (hasZeroSumSubarray(testCases[i]))
        {
            cout << "Zero-sum subarray exists\n";
        }
        else
        {
            cout << "No zero-sum subarray\n";
        }
    }

    return 0;
}

/*

🔍 Approach: Prefix Sum + Hashing

- We iterate through the array while maintaining the cumulative (prefix) sum.
- If the prefix sum becomes 0, then the subarray from the start to that index sums to 0.
- If a prefix sum is **seen again**, then the elements between the two occurrences must sum to 0.

📌 Why repeated prefix sum ⇒ 0-sum subarray?
    Let’s say prefixSum[i] = prefixSum[j] (where i < j)
    Then sum(i+1 to j) = prefix[j] - prefix[i] = 0
    So the subarray between i+1 and j has total sum 0.

💡 Detailed Example:
    arr = {1, 4, -2, -2, 5, -4, 3}
    
    Let's compute the prefix sums:
    - Index 0 → 1             → sum = 1
    - Index 1 → 1+4 = 5       → sum = 5
    - Index 2 → 5 + (-2) = 3  → sum = 3
    - Index 3 → 3 + (-2) = 1  → sum = 1  ✅ (prefix sum 1 is repeating)
    - Index 4 → 1 + 5 = 6
    - Index 5 → 6 + (-4) = 2
    - Index 6 → 2 + 3 = 5     ✅ (prefix sum 5 is repeating)

    Two prefix sums repeat:
    - First repetition: prefix sum 1 at index 0 and 3 → subarray [1, 4, -2, -2] → sum = 0
    - Second repetition: prefix sum 5 at index 1 and 6 → subarray [5, -4, 3] → sum = 0

✅ So the array contains at least one subarray with sum = 0.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) – storing prefix sums in a set

*/
