/*
Approach:

We are performing binary search in two different ways:

1. Row-wise Binary Search:
   - We go through each row and apply binary search.
   - Time Complexity: O(n * log m)
     where n = number of rows, m = number of columns

2. Column-wise Binary Search:
   - We go through each column and apply binary search.
   - Time Complexity: O(m * log n)
     where n = number of rows, m = number of columns

Note: In practice, if the matrix is sorted row-wise and column-wise,
it's better to use the "staircase" search from top-right corner for O(m + n) time,
but this implementation demonstrates binary search based approaches.
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int target) 
    {
        int rows = mat.size();
        int cols = mat[0].size();

        // we can search target in each row using binary search
        for (int row = 0; row < rows; row++) {
            if (binarySearchRow(mat, row, target)) {
                return true;
            }
        }

        // OR
        // we can search target in each column using binary search
        for (int col = 0; col < cols; col++) {
            if (binarySearchCol(mat, col, target)) {
                return true;
            }
        }

        return false;
    }

private:
    // Binary Search in a given row
    bool binarySearchRow(vector<vector<int>>& mat, int row, int target) {
        int left = 0, right = mat[0].size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mat[row][mid] == target) {
                return true;
            } else if (mat[row][mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }

    // Binary Search in a given column
    bool binarySearchCol(vector<vector<int>>& mat, int col, int target) {
        int top = 0, bottom = mat.size() - 1;

        while (top <= bottom) {
            int mid = top + (bottom - top) / 2;
            if (mat[mid][col] == target) {
                return true;
            } else if (mat[mid][col] < target) {
                top = mid + 1;
            } else {
                bottom = mid - 1;
            }
        }
        return false;
    }
};
