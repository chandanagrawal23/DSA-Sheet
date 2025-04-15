class Solution {
public:
    // Main function to find all combinations that sum up to the target
    vector<vector<int>> combinationSum(vector<int>& a, int target) {
        // Vector to store the final combinations
        vector<vector<int>> ans;
        
        // Vector to store the current combination being built
        vector<int> combi;
        
        // Sort the input array to help with pruning
        sort(a.begin(), a.end());
        
        // Call the backtracking function to generate combinations
        backtrack(a, target, combi, ans, 0);
        
        // Return the list of all valid combinations
        return ans;
    }

    // Backtracking function to generate combinations
    void backtrack(vector<int>& a, int target, vector<int> combi, vector<vector<int>>& ans, int begin) {
        // If the target is negative, stop exploring this path
        if (target < 0) 
            return;
        
        // If the target is exactly zero, we've found a valid combination
        if (target == 0) {
            ans.push_back(combi);  // Add the current combination to the answer list
            return;
        }

        // Iterate through the array starting from 'begin' index
        for (int i = begin; i < a.size(); i++) {
            // If the current number can be part of the combination
            if (target >= a[i]) {
                // Add the number to the current combination
                combi.push_back(a[i]);
                
                // Recursively call backtracking with the reduced target
                // We pass 'i' instead of 'i+1' to allow repeated use of the same number
                backtrack(a, target - a[i], combi, ans, i);
                
                // Remove the last element (backtrack) to explore other possibilities
                combi.pop_back();
            } 
            else {
                // If the current number is greater than the target, stop further exploration
                break;
            }
        }
    }
};
