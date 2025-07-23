class Solution
{
public:
    vector<long long> distance(vector<int> &arr)
    {
        int n = arr.size();
        vector<long long> output(n, 0);
        unordered_map<int, long long> sumOfIndexes;
        unordered_map<int, int> countOfIndexes;

        // Left to Right Pass
        for (int i = 0; i < n; ++i)
        {
            int val = arr[i];
            if (sumOfIndexes.count(val))
            {
                //            the current index * count - total sum of indices so far
                output[i] += (1LL * i * countOfIndexes[val]) - sumOfIndexes[val];
            }

            sumOfIndexes[val] += i;
            countOfIndexes[val]++;
        }

        sumOfIndexes.clear();
        countOfIndexes.clear();

        // Right to Left Pass
        for (int i = n - 1; i >= 0; --i)
        {
            int val = arr[i];
            if (sumOfIndexes.count(val))
            {
                //          sum of indices so far from right - the current index i  * count 
                output[i] += sumOfIndexes[val] - (1LL * i * countOfIndexes[val]);
            }

            sumOfIndexes[val] += i;
            countOfIndexes[val]++;
        }

        return output;
    }
};

/*
Approach:
- For each index i, we want to compute the total distance (absolute difference in indices)
  between i and every other index j such that arr[i] == arr[j].

    Consider 1's at different postions of an array. 
    x  y  z   p   q
    1  1  1   1   1

    consider 1 at index z: |z - x| + |z - y| + |z - p| + |z - q|

    when we are looping from left to right we are storing sum and count of previous indices of num in maps.
    |z - x| + |z - y| = z - x + z - y, since z is greater than x and y.
    z - x + z - y = 2z - (x + y) = (count) * (currentIndex) - (sum).

    Similarly we can calculate the |z - p| + |z - q| when we loop from right to left aka - 

    |z - p| + |z - q| = p - z + q - z, since index p and q are greater than index z

    => p - z + q - z = (p + q) - 2z = sum - (count) * (currentIndex)

- To avoid O(N^2), we use prefix sum tricks:

    1. Left-to-Right Pass:
        - For each number, maintain:
            - count: how many times it has appeared so far
            - sum: total of all indices it has appeared at so far
        - For current index i:
            - Total distance to previous same-value indices:
              = i * count - sum

    2. Right-to-Left Pass:
        - Reuse the same formula!
        - For each number, maintain:
            - count: how many times it has appeared so far (from the right)
            - sum: sum of their indices
        - For current index i:
            - Total distance to future same-value indices:
              = sum - i * count

        This also works because absolute distance |i - j| is symmetric:
            → |i - j| = |j - i|

        So both formulas are essentially:
            → distance = |i - j₁| + |i - j₂| + ... = count * i - sum  (for any j)

- By combining both passes, we get total distance for each index to all other same-value indices.

Time Complexity: O(n)
- Each pass is linear.

Space Complexity: O(n)
- Hash maps store count and sum for each unique number.
*/
