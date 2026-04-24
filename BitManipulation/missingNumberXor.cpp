class Solution 
{
public:
    int missingNumber(vector<int>& nums) 
    {
        int n = nums.size();
        int xorAll = 0;

        // XOR of 0 to n
        for(int i = 0; i <= n; i++)
        {
            xorAll ^= i;
        }

        // XOR of array elements
        for(int num : nums)
        {
            xorAll ^= num;
        }

        return xorAll;
    }
};

/*
Approach:
- XOR all numbers from 0 to n
- XOR all elements of array
- Common elements cancel out
- Remaining value is the missing number

Time Complexity: O(n)
Space Complexity: O(1)
*/
