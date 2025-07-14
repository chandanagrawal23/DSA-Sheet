class Solution 
{
public:
    vector<int> singleNumber(vector<int>& nums) 
    {
        int XOR = 0;

        // Step 1: XOR all numbers together.
        // XOR of two same numbers is 0 and XOR of any number with 0 is the number itself.
        // At the end, XOR will hold the result of XORing the two distinct numbers.
        for (auto xt : nums) 
        {
            XOR = XOR ^ xt;
        }
        
        // Step 2: Find the rightmost set bit (where XOR is 1)
        // This bit will be different in the two numbers we are looking for.
        int i = 0;
        while (true) 
        {
            if (XOR & (1 << i)) 
            {
                break;  // Found the first bit that is set
            }
            i++;  // Move to the next bit
        }
        
        int val = 1 << i;  // This is the bitmask with the i-th bit set
        
        vector<int> ans(2, 0);  // To store the two distinct numbers

        // Step 3: Divide the numbers into two groups based on the i-th bit being set or not
        for (auto xt : nums) 
        {
            if (xt & val) 
            {
                ans[0] = ans[0] ^ xt;  // XOR all numbers in this group
            } 
            else 
            {
                ans[1] = ans[1] ^ xt;  // XOR all numbers in this group
            }
        }

        return ans;  // Return the two distinct numbers
    }
};

/*
Approach:

- Step 1: XOR all elements in the array. The result will be the XOR of the two numbers that appear once, because XORing the same number results in 0.
- Step 2: Find the rightmost set bit in the XOR result. This bit is different between the two unique numbers. It helps to divide the numbers into two groups.
- Step 3: Divide the array into two groups: one where the corresponding bit is set and one where it is not. XOR the numbers in each group, and you'll get the two distinct numbers.

Time complexity: O(n), where n is the number of elements in the array. We pass through the array a couple of times.
Space complexity: O(1), as we only use a fixed amount of extra space.
*/
