class Solution {
public:
   // when we start from top right 
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int n = mat.size();        // Total rows
        int m = mat[0].size();     // Total columns

        int i = 0;         // Start from top-right corner (0, m-1)
        int j = m - 1;

        while (i < n && j >= 0) {
            if (mat[i][j] == target) {
                return true;       // Target found
            }
            else if (mat[i][j] > target) {
                // Since the current element is greater than the target,
                // and all elements to the left are smaller in the same row,
                // we move left to explore smaller elements
                j--;
            }
            else {
                // Since the current element is smaller than the target,
                // and all elements below in the same column are larger,
                // we move down to explore larger elements
                i++;
            }
        }

        return false; // Target not found
    }

 // when we start from bottom left
  bool searchMatrix(vector<vector<int>>& mat, int target) {
        int n = mat.size();        // Total rows
        int m = mat[0].size();     // Total columns

        int i = n - 1;     // Start from bottom-left corner (n-1, 0)
        int j = 0;

        while (i >= 0 && j < m) {
            if (mat[i][j] == target) {
                return true;       // Target found
            }
            else if (mat[i][j] > target) {
                // Since the current element is greater than the target,
                // and all elements above in the same column are smaller,
                // we move up to explore smaller elements
                i--;
            }
            else {
                // Since the current element is smaller than the target,
                // and all elements to the right in the same row are larger,
                // we move right to explore larger elements
                j++;
            }
        }

        return false; // Target not found
    }
};
