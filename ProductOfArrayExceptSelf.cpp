class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // Get the size of the input array
        int n = nums.size();

        // Initialize variables to keep track of the product from the beginning and the end
        int fromBegin = 1;
        int fromLast = 1;

        // Result vector to store the final output, initialized with 1s
        vector<int> res(n, 1);

        // First pass: Traverse the array from left to right
        // Multiply the result by the product of all elements before the current element
        for(int i = 0; i < n; i++) {
            res[i] *= fromBegin;   // Multiply the result by the product of elements before the current index
            fromBegin *= nums[i];  // Update the product of elements from the beginning up to the current element
        }

        // Second pass: Traverse the array from right to left
        // Multiply the result by the product of all elements after the current element
        for(int i = n - 1; i >= 0; i--) {
            res[i] *= fromLast;   // Multiply the result by the product of elements after the current index
            fromLast *= nums[i];  // Update the product of elements from the end up to the current element
        }

        // Return the final result vector
        return res;
    }
};
