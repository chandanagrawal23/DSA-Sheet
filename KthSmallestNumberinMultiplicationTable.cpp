class Solution
{
public:
    // Count numbers ≤ mid in m x n multiplication table
    int countLessEqual(int mid, int m, int n)
    {
        int cnt = 0;
        for (int i = 1; i <= m; i++)
        {
            cnt += min(mid / i, n); // Each row i has min(mid/i, n) values ≤ mid
        }
        return cnt;
    }

    int findKthNumber(int m, int n, int k)
    {
        int left = 1, right = m * n;
        int ans = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (countLessEqual(mid, m, n) >= k)
            {
                ans = mid;        // mid is a valid candidate
                right = mid - 1;  // look for a smaller one
            }
            else
            {
                left = mid + 1;   // kth number must be on the right
            }
        }

        return ans;
    }
};

/*

Approach:
- Given an m x n multiplication table, find the kth smallest number.
- The multiplication table is sorted in both row and column order.

Steps:
1. Perform binary search on the value range [1, m * n].
2. For each candidate value `mid`, count how many numbers in the table are ≤ mid.
   - For row i: count is min(mid / i, n)
   - Total count = sum of these row counts
3. If count ≥ k → `mid` could be a valid answer → try smaller values (search left)
4. If count < k → not enough values ≤ mid → search right

Why this works:
- We're not searching positions, but actual values.
- This is possible because the table is monotonic in both directions.

Time: O(m * log(m * n))  
Space: O(1)

*/
