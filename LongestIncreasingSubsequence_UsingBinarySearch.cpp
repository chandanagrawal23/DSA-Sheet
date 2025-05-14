/* ****************************************************** USING Plain Binary Search *********************************************** */

class Solution
{
public:
    // Function to calculate the length of the Longest Increasing Subsequence (LIS)
    int lengthOfLIS(vector<int>& nums)
    {
        // This will store the smallest possible tail element for all increasing subsequences of different lengths
        vector<int> res;

        // Iterate through each number in the input array
        for (int val : nums)
        {
            // If current number is greater than the last element in res, it extends the LIS
            if (res.empty() || res.back() < val)
            {
                res.push_back(val);
            }
            else
            {
                // Otherwise, find the index of the first element in `res` which is greater than or equal to `val`
                // This means we can replace that element with `val` to potentially start a new increasing subsequence
                // of the same length but with a smaller ending element — keeping future LIS options open.
                int ansIndex = binarySearch(res, val);
                res[ansIndex] = val;
            }
        }

        // The size of res gives the length of the LIS
        return res.size();
    }

private:
    // Helper function to find the index of the smallest element >= target
    int binarySearch(const vector<int>& arr, int target)
    {
        int left = 0, right = arr.size() - 1;
        int ansIndex = arr.size();  // Default value if target is larger than all elements

        // Standard binary search
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            // If current mid value is >= target, it is a potential candidate for replacement
            if (arr[mid] >= target)
            {
                ansIndex = mid;
                right = mid - 1;  // Try to find an even smaller index
            }
            else
            {
                left = mid + 1;
            }
        }

        return ansIndex;
    }
};

/* ****************************************************** USING LOWER BOUND *********************************************** */

class Solution 
{
public:
    int lengthOfLIS(vector<int>& nums) 
    {
        // This vector stores the smallest possible tail values for increasing subsequences
        vector<int> res;

        for (int i = 0; i < nums.size(); i++) 
        {
            // Find the first element in `res` that is >= nums[i]
            // This maintains the smallest tail element for each length
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);

            if (it == res.end()) 
            {
                // If nums[i] is greater than all elements, extend the LIS
                res.push_back(nums[i]);
            } 
            else 
            {
                // Replace the found element to keep the subsequence optimal
                *it = nums[i];
            }
        }

        // The size of `res` gives the length of the Longest Increasing Subsequence
        return res.size();
    }
};
