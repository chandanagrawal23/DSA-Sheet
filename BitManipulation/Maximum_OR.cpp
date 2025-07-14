class Solution 
{
public:
    long long maximumOr(vector<int>& nums, int k) 
    {
        int n = nums.size();
        long long result = 0;

        // prefix[i] stores OR of nums[0] to nums[i-1] (excluding nums[i])
        // suffix[i] stores OR of nums[i+1] to nums[n-1] (excluding nums[i])
        vector<int> prefix(n + 1, 0), suffix(n + 1, 0);

        // Build prefix OR values
        for (int i = 1; i < n; i++)
        {
            prefix[i] = prefix[i - 1] | nums[i - 1];
        }

        // Build suffix OR values
        for (int i = n - 2; i >= 0; i--)
        {
            suffix[i] = suffix[i + 1] | nums[i + 1];
        }

        // Try shifting each nums[i] and calculate maximum OR result
        for (int i = 0; i < n; i++) 
        {
            // Shift current number by k bits to the left
            long long shiftByK = (long long)nums[i] << k;

            // Combine prefix OR + shifted value + suffix OR
            long long totalOR_AfterShifts = prefix[i] | shiftByK | suffix[i];

            // Track the maximum result
            result = max(result, totalOR_AfterShifts);
        }

        return result;
    }
};

/*

🧠 Intuition:
To maximize the overall OR value after applying the left shift operation to exactly one element,
you should pick the number whose shifted value contributes the most to the total.

🔧 Strategy:
- Instead of shifting multiple numbers, it's optimal to shift **only one** number.
------------------------------------------------------------------------------------------------
WHY ? 
🧠 Why shifting one number is not just optimal, but provably best:
Let’s say:
You have a number x with highest bit at position b
Shifting x by k → now highest bit at b + k
If you instead split:
x << i and y << (k - i) → highest bit is max(bx + i, by + k - i)
But both are less than (or equal to) max(bx, by) + k
So better to apply full shift on one with max bx
-------------------------------------------------------------------------------------------

- For each index `i`, simulate shifting nums[i] by `k` bits.
- Then combine:
    → prefix OR from index 0 to i-1
    → shifted value of nums[i]
    → suffix OR from i+1 to n-1

📊 Why prefix & suffix?
- We want to avoid recomputing ORs from scratch each time.
- prefix[i] holds OR of all elements before i
- suffix[i] holds OR of all elements after i

🧪 Example:
nums = [8, 1, 2], k = 2

→ Try shifting each:
- shift 8 → 32 → OR = 32 | 1 | 2 = 35
- shift 1 → 4  → OR = 8 | 4 | 2 = 14
- shift 2 → 8  → OR = 8 | 1 | 8 = 9

✅ Max = 35

⏱ Time Complexity: O(n)
🧠 Space Complexity: O(n)


*/
