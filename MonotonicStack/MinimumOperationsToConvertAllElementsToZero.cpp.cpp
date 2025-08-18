// Brute Force ( Learn this first )

class Solution
{
public:
    int minOperations(vector<int>& nums)
    {
        unordered_set unique(nums.begin(), nums.end());
        int ans = 0;

        for (int num : unique) 
        {
            if (num == 0) 
                continue;
            bool inBlock = false;
            for (int i = 0; i < nums.size(); i++) 
            {
                if (nums[i] == num) 
                {
                    if (!inBlock) 
                    {
                        inBlock = true;
                        ans++;
                    }
                } 
                else if(nums[i] < num) // end the block when smaller element was found 
                {  
                    inBlock = false;
                }
            }
        }
        return ans;
    }
};
/*
Approach (Brute Force):

1. For each unique value > 0 in the array:
   - Scan the array from left to right.
   - Count how many disjoint blocks of this value exist.
   - A block continues until we encounter a smaller element,
     which forces the block to break.
2. Add up the block counts for all unique values.

For each unique number x > 0 in nums, find how many disjoint subarrays in which current element is minimum and cover all its occurrences.

For example, if the array is [1, 2, 3, 2, 3, 2, 1, 1, 1, 2]:

For 1: we can remove all 1s in a single operation using a large enough subarray → [1, 2, 3, 2, 3, 2, 1, 1, 1] = 1 operation
For 2: the 2s are broken across: [2,3,2,3,2], [2], hence ans += 2
Total operations = 3 so far, and similarly for 3.
For 3: [3], [3] blocks, that is ans += 2.
Final ans = 5.

Time Complexity: O(n * U)
    - n = length of array
    - U = number of unique elements
    - For each unique value we scan the entire array.

Space Complexity: O(U)
    - To store the set of unique elements.
*/

//========================================== MONOTONIC STACK ==================================================

class Solution
{
public:
    int minOperations(vector<int>& nums)
    {
        stack<int> st;
        int ans = 0;

        for (int x : nums)
        {
            // Pop larger elements (they must be removed before x anyway)
            while (!st.empty() && st.top() > x)
            {
                st.pop();
            }

            // If x is strictly greater than top OR stack empty → new block
            if (st.empty() || st.top() < x)
            {
                if (x > 0) // ignore zeros
                {
                    ans++;
                    st.push(x);
                }
            }
            // else (st.top() == x): already counted, skip
        }

        return ans;
    }
};

/*
Approach (Monotonic Stack):

1. Every new "block" is counted when the current element cannot be merged into
   an existing smaller chain.
2. If current element > top of stack → we need a new block (push it).
3. If current element < top of stack → we pop until we find a smaller or equal element,
   because larger values will be removed earlier anyway.
4. If current element == top of stack → it is already counted, so skip.

Time Complexity: O(n)   (each element pushed and popped at most once)
Space Complexity: O(n)  (stack in worst case)
*/
