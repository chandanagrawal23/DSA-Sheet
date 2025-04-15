class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& a) {
        // Get the size of the input array
        int n = a.size();

        // Vector to store all subsets
        vector<vector<int>> ans;
        
        // Set to store subsets to handle duplicates
        set<vector<int>> st;

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

            // Sort the current subset to ensure that identical subsets are in the same order
            sort(temp.begin(), temp.end());

            // If this subset has not been encountered before (not in the set), add it to the result
            if(st.count(temp) == 0) {
                ans.push_back(temp);
                st.insert(temp);  // Insert this subset into the set to avoid duplicates
            }
        }

        // Return the list of unique subsets
        return ans;
    }
};
