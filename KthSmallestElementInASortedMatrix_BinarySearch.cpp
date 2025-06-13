class Solution
{
public:
    // Count how many values in the matrix are ≤ target
    int countLessEqual(vector<vector<int>> &mat, int target)
    {
        int count = 0;
        int n = mat.size();
        int col = n - 1;

        for (int row = 0; row < n; row++)
        {
            // Move left while values are greater than target
            while (col >= 0 && mat[row][col] > target)
                col--;

            count += (col + 1); // All elements from 0 to col are ≤ target
        }
        return count;
    }

    int kthSmallest(vector<vector<int>> &mat, int k)
    {
        int n = mat.size();

        int left = mat[0][0];         // Smallest element
        int right = mat[n - 1][n - 1]; // Largest element
        int answer = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (countLessEqual(mat, mid) < k)
            {
                left = mid + 1; // Need more values ≤ mid
            }
            else
            {
                answer = mid;    // mid is a possible answer
                right = mid - 1; // Try for a smaller one
            }
        }

        return answer;
    }
};

/*

Approach:
- The matrix is row-wise and column-wise sorted.
- Perform binary search on the value range: [min, max] of matrix.
- For each mid, count how many numbers are ≤ mid using top-right to bottom-left scan.
- If count < k → need larger values → move right.
- Else → mid is a candidate → try left to find smaller.

Time: O(n * log(max - min)), where n = #rows = #cols
Space: O(1)

*/
