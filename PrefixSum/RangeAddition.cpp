#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> getModifiedArray(int length, vector<vector<int>> &updates)
    {
        vector<int> result(length, 0);

        // Apply the difference array concept
        for (auto &op : updates)
        {
            int start = op[0];
            int end = op[1];
            int inc = op[2];

            result[start] += inc;

            if (end + 1 < length)
            {
                result[end + 1] -= inc;
            }
        }

        // Convert difference array to prefix sum array
        for (int i = 1; i < length; i++)
        {
            result[i] += result[i - 1];
        }

        return result;
    }
};

/*
Approach:
- We use the Difference Array technique for efficient range updates.
- For each operation [start, end, inc], instead of updating the whole range,
  we update only two positions:
    → Add 'inc' at start index
    → Subtract 'inc' at (end + 1) index (if within bounds)

Why subtract at (end + 1)?
- Because we want the increment to apply from 'start' to 'end' (inclusive),
  and then STOP after 'end'.
- By subtracting at (end + 1), when we compute the prefix sum later, the
  added value stops contributing beyond 'end'.
- Think of it like a running effect that starts at 'start' and is cancelled at 'end + 1'.

Example:
  updates = [[1,3,2]]
  After marking:
      result[1] += 2    → starts adding 2 from index 1
      result[4] -= 2    → cancels out 2 after index 3 (i.e., at 4)

  Then prefix sum will ensure:
    result[1..3] += 2
    result[4..n-1] += 0 (no effect)

Time Complexity: O(k + n)
- O(k) to apply k updates using difference array
- O(n) to compute final result via prefix sum

Space Complexity: O(n)
- One array of size 'n' to store the result
*/
