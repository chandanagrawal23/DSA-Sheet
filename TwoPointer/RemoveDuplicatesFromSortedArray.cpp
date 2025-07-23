class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();

        if (n < 2)
          return n; // Already unique

        int idx = 1; // Index to place the next unique element

        for (int i = 1; i < n; ++i)
        {
            // If current number is different from previous, it's unique
            if (nums[i] != nums[i - 1])
            {
                nums[idx] = nums[i];
                idx++;
            }
        }

        return idx; // Length of unique prefix
    }
};

/*
Approach:
- Given a sorted array, remove duplicates in-place.
- Use two pointers:
    - One (i) for iterating through the array
    - Second (idx) to track the position for the next unique element
- If current element nums[i] ≠ nums[i - 1], it's a new unique number.
    - Place it at nums[idx] and increment idx.
- In the end, elements [0..idx-1] are the deduplicated sorted array.

Time Complexity: O(n)
- Single pass through the array.

Space Complexity: O(1)
- In-place updates, no extra space used.
*/
