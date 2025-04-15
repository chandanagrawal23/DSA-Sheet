class Solution {
public:    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        vector<int> visited(nums.size(), false);
        int sum = 0;
        for (auto x : nums) 
            sum += x;  // Calculate total sum.
        if (sum % k != 0)
            return false;  // If sum is not divisible by k, return false.
        
        int targetsum = sum / k;  // Calculate the required sum for each subset.
        return dfs(nums, visited, 0, k, 0, targetsum);  // Start DFS to partition.
    }

                                        // currsum is the current sum of subset, targetsum is the required sum for each subset.
    bool dfs(vector<int>& nums, vector<int> visited, int idx, int k, int currsum, int targetsum) {
        if (k == 1) return true;  // If k==1, all subsets have been found, return true.
        if (currsum == targetsum) return dfs(nums, visited, 0, k - 1, 0, targetsum);  // Found one subset, start from the beginning for the next subset.
        
        for (int i = idx; i < nums.size(); i++) {
            if (!visited[i] && (currsum + nums[i]) <= targetsum) {  // If index is not visited, can be used in current subset.
                visited[i] = true;  // Mark index as used , set to true
                if (dfs(nums, visited, i + 1, k, currsum + nums[i], targetsum)) return true;  // Explore the choices.
                visited[i] = false;  // Backtrack , reset back to false
            }
        }
        return false;  // Return false if no valid partition found.
    }

};
