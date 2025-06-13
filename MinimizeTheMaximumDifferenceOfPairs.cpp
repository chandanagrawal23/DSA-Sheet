class Solution
{
public:
    // Count how many valid pairs exist with given threshold
    int countValidPairs(vector<int>& nums, int threshold)
    {
        int i = 0, pairs = 0;
        while (i < nums.size() - 1)
        {
            // If adjacent pair difference is <= threshold, count it
            if (nums[i + 1] - nums[i] <= threshold)
            {
                pairs++;
                i++;  // Skip next to avoid overlapping pair
            }
            i++;
        }
        return pairs;
    }

    int minimizeMax(vector<int>& nums, int p)
    {
        sort(nums.begin(), nums.end());  // Sort to form closest pairs
        int left = 0;
        int right = nums.back() - nums.front();

        int ans = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            // Check if we can form at least p valid pairs with this threshold
            if (countValidPairs(nums, mid) >= p)
            {
                ans = mid;
                right = mid-1;  // Try smaller threshold
            }
            else
            {
                left = mid + 1;  // Increase threshold
            }
        }

        return ans;
    }
};

/*
Approach:
- Sort array to bring closer elements next to each other.
- Use binary search to minimize the max absolute difference among p pairs.
- Greedily count valid pairs for each mid threshold.

Time Complexity:  O(n log n + n log D)
    - Sort: O(n log n)
    - Binary search over D range (max-min): O(log D), each with O(n)
Space Complexity: O(1) extra (in-place sorting and constant space used)
*/
