class Solution 
{
public:
    vector<vector<int>> subsets(vector<int>& a) 
    {
        int n = a.size();  // Get the size of the input array
        vector<vector<int>> ans;  // Vector to store all subsets
        
        // Loop through all numbers from 0 to (2^n - 1) to generate subsets
        for (int i = 0; i < (1 << n); i++) 
        {
            vector<int> temp;  // Temporary vector to store a single subset

            // Loop through each bit of the number 'i' to decide which elements to include in the subset
            for (int j = 0; j < n; j++) 
            {
                // If the j-th bit of i is set, include the corresponding element from 'a'
                if (i & (1 << j)) 
                {
                    temp.push_back(a[j]);
                }
            }

            // Add the subset to the result list
            ans.push_back(temp);
        }

        return ans;  // Return all subsets
    }
};

/*
Approach:

- Use a binary representation to represent subsets. For a set of size n, we have 2^n possible subsets.
- Iterate through numbers 0 to 2^n - 1. Each number represents a subset where the set bits indicate which elements from the input array are included in that subset.
- For each subset, add it to the result list.

Time complexity: O(2^n * n), as there are 2^n subsets and for each subset, we may need to loop through n elements.  
Space complexity: O(2^n), for storing all subsets.
*/
