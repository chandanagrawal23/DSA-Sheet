class Solution
{
public:
    int removeDuplicates(vector<int> &nums, int k=2)
    {
        int n = nums.size();

        if (n <= k)
        {
            return n;
        }

        int index = k; // Start writing from index k , at most k times a valyue appear here k is 2

        for (int i = k; i < n; i++)
        {
            // Compare current with the element k positions back
            if (nums[i] != nums[index - k])
            {
                nums[index] = nums[i];
                index++;
            }
        }

        return index;
    }
};
/*
Approach:
- Same logic as before, just generalized for any `k` allowed duplicates.
- Allow the first `k` elements by default.
- For each new element from index `k` onwards:
    - Compare it with `nums[index - k]`.
    - If they differ, the current value hasn't appeared more than `k` times yet, so write it at index.

Example:
nums = [1,1,1,2,2,2,3], k = 2
→ Output: [1,1,2,2,3] → First 5 elements

Time Complexity: O(n)
Space Complexity: O(1)
*/
