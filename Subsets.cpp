class Solution {
public:
    vector<vector<int>> subsets(vector<int>& a) {
        // Get the size of the input array
        int n = a.size();
        
        // Vector to store all subsets
        vector<vector<int>> ans;

        // Loop through all possible subsets (from 0 to 2^n - 1)
        for(int i = 0; i < (1 << n); i++) {
            // Temporary vector to store the current subset
            vector<int> temp;

            // Loop through each bit of the number 'i' to decide which elements to include
            for(int j = 0; j < n; j++) {
                // If the j-th bit of 'i' is set (i.e., 1), include a[j] in the subset
                if(i & (1 << j)) {
                    temp.push_back(a[j]);
                }
            }

            // Add the current subset (temp) to the answer vector
            ans.push_back(temp);
        }

        // Return the list of all subsets
        return ans;
    }
};
