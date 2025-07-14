class Solution 
{
public:
    int singleNumber(vector<int>& nums) 
    {
        int bits[32] = {0};  // Array to store the frequency of bits for each position

        // Loop through each bit position (0 to 31)
        for (int i = 0; i < 32; i++) 
        {
            // Check each number in the input array
            for (auto xt : nums) 
            {
                // If the i-th bit of the number is set, increment the count
                if (xt & (1 << i)) 
                {
                    bits[i]++;
                    bits[i] %= 3;  // Since the number appears 3 times, we take modulo 3
                }
            }
        }

        int ans = 0;  // Variable to store the final result

        // Reconstruct the number from the bits array
        for (int i = 0; i < 32; i++) 
        {
            if (bits[i]) 
            {
                ans += (1 << i);  // Set the i-th bit of the result
            }
        }

        return ans;  // Return the single number
    }
};

/*
Approach:

- The idea is to use the bit manipulation technique to track the frequency of each bit in the array.
- We know that every number appears exactly 3 times, except one number which appears only once.
- We count the occurrence of each bit in all the numbers using an array `bits[]`. We take modulo 3 to keep track of the number that appears once.
- After counting, we reconstruct the single number by checking the bits array.

Time complexity: O(32 * n), where n is the number of elements in the array. We loop over each bit position for all the elements.
Space complexity: O(32), for storing the bit frequencies of 32 positions.
*/
