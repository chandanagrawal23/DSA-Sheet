class Solution
{
public:
    vector<int> twoSum(vector<int> &a, int target)
    {
        int i = 0;
        int j = a.size() - 1;

        while (i < j)
        {
            int sum = a[i] + a[j];

            if (sum == target)
            {
                return {i + 1, j + 1}; // 1-based index as per problem
            }
            else if (sum < target)
            {
                i++;
            }
            else
            {
                j--;
            }
        }

        return {}; // No solution found
    }
};

/*
Approach:
- Use two pointers on the sorted array: one at the start, one at the end.
- If sum is too small, move left pointer to increase it.
- If sum is too large, move right pointer to decrease it.
- Return 1-based indices when sum matches target.

Time Complexity: O(N)
- Single linear pass from both ends.

Space Complexity: O(1)
- No extra space used except output.
*/
