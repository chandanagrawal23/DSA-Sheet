class Solution {
public:
    // Main function to find all unique combinations that sum up to the target
    vector<vector<int>> combinationSum2(vector<int>& cand, int target) {
        // Vector to store the final unique combinations
        vector<vector<int>> ans;
        
        // Sort the candidates to help with pruning and skipping duplicates
        sort(cand.begin(), cand.end());
        
        // Temporary vector to store a single combination
        vector<int> temp;
        
        // Call the backtracking function to generate combinations
        backtrackCombination(ans, temp, cand, 0, target);
        
        // Return the list of all valid unique combinations
        return ans;
    }

    // Backtracking function to explore combinations recursively
    void backtrackCombination(vector<vector<int>>& ans, vector<int>& temp, const vector<int>& cand, int index, int target) {
        // Base case: if the target becomes 0, we have found a valid combination
        if (target == 0) {
            ans.push_back(temp);  // Add the current combination to the answer
            return;
        }

        // Iterate through the candidates starting from the current index
        for (int i = index; i < cand.size(); i++) {
            // If the current candidate exceeds the remaining target, stop further exploration
            if (cand[i] > target) {
                return;  // No need to backtrack further as all candidates are sorted
            }
            
            // Skip duplicates: If the current candidate is the same as the previous one, skip it
            if (i > index && cand[i] == cand[i - 1]) {
                continue;  // Skip this candidate to avoid duplicate combinations
            }
            
            // Include the current candidate in the combination
            temp.push_back(cand[i]);
            
            // Recurse with the updated target and next index (i + 1 to avoid reusing the same element)
            backtrackCombination(ans, temp, cand, i + 1, target - cand[i]);
            
            // Backtrack by removing the last element to explore other possibilities
            temp.pop_back();
        }
    }
};
