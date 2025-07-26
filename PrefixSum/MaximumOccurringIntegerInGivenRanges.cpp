#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxOccuredElement(int n, vector<int> &L, vector<int> &R)
    {
        const int MAX = 1e6 + 2;  // As per constraint

        vector<int> freq(MAX, 0);

        // Apply difference array logic: +1 at L[i], -1 at R[i]+1
        for (int i = 0; i < n; i++)
        {
            freq[L[i]] += 1;

            if (R[i] + 1 < MAX)
            {
                freq[R[i] + 1] -= 1;
            }
        }

        // Build prefix sum and track max frequency and its index
        int maxFreq = freq[0];
        int result = 0;

        for (int i = 1; i < MAX; i++)
        {
            freq[i] += freq[i - 1];

            if (freq[i] > maxFreq)
            {
                maxFreq = freq[i];
                result = i;
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;

    // Test Case 1
    vector<int> L1 = {1, 4, 3, 1};
    vector<int> R1 = {15, 8, 5, 4};
    cout << "Output 1: " << sol.maxOccuredElement(L1.size(), L1, R1) << endl;

    // Test Case 2
    vector<int> L2 = {1, 5, 9, 13, 21};
    vector<int> R2 = {15, 8, 12, 20, 30};
    cout << "Output 2: " << sol.maxOccuredElement(L2.size(), L2, R2) << endl;

    return 0;
}
/*
Approach:
- Use 1D difference array to handle multiple range updates efficiently.
- For each range [L[i], R[i]]:
    → Add +1 at L[i]
    → Subtract -1 at R[i]+1 to cancel beyond range

- Then compute prefix sum over entire array to get actual frequency of occurrence.
- Track the number (index) with highest frequency.

If multiple numbers have the same frequency, the smallest one is selected naturally
since we update result only when we find a new higher frequency.

Time Complexity: O(n + max(R[i]))
Space Complexity: O(max(R[i])) = ~1e6
*/
