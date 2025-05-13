class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int rows = mat.size();  // Get number of rows in the matrix
        int cols = mat[0].size();  // Get number of columns in the matrix
        
        int left = 0;  // Start of the flattened matrix
        int right = (rows * cols) - 1;  // End of the flattened matrix
        
        while (left <= right) {  // Binary search loop
            int mid = left + (right - left) / 2;  // Find middle index
            
            // Convert the mid index to row and column numbers
            int rowNumber = mid / cols;  // Row number in the matrix
            int columnNumber = mid % cols;  // Column number in the matrix
            
            int midElement = mat[rowNumber][columnNumber];  // Value at the mid position
            
            // Check if the mid element is the target
            if (midElement == target) {
                return true;
            }
            // If the mid element is greater than the target, search the left half
            else if (midElement > target) {
                right = mid - 1;
            }
            // If the mid element is less than the target, search the right half
            else {
                left = mid + 1;
            }
        }
        
        return false;  // If target is not found
    }
};
