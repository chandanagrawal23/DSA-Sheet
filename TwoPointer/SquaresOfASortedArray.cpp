class Solution
{
public:
    vector<int> sortedSquares(vector<int> &A)
    {
        int n = A.size();
        vector<int> result(n, 0);

        int left = 0;
        int right = n - 1;

        // Fill result from the back with the largest squares first
        for (int pos = n - 1; pos >= 0; --pos)
        {
            if (abs(A[left]) > abs(A[right]))
            {
                result[pos] = A[left] * A[left];
                left++;
            }
            else
            {
                result[pos] = A[right] * A[right];
                right--;
            }
        }

        return result;
    }
};

/*
Approach:
- Since the input array is sorted (possibly with negatives), the largest squares will be at the ends.
- Use two pointers: one at the beginning and one at the end.
- Compare absolute values, place the larger square at the end of the result array, and move pointers accordingly.

Time Complexity: O(N)
- One pass from both ends.

Space Complexity: O(N)
- Output array of same size.
*/
