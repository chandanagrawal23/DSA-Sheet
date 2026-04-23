class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans = "";   // use this as a stack to build the smallest number
       
        for (char c : num) 
        {
            // Greedy: remove bigger digits from left if current digit is smaller
            // This ensures final number is lexicographically smallest
            while (ans.length() && ans.back() > c && k) 
            {
                ans.pop_back();   // remove previous larger digit
                k--;              // one removal done
            }

            // Avoid leading zeros
            if (ans.empty())
            {
                if (c != '0')
                    ans.push_back(c);
            }  
            else
            {
                ans.push_back(c); // normal push
            }
        }
       
        // If still removals left, remove from end (largest remaining digits)
        while (ans.length() && k--) 
        {
            ans.pop_back();
        }
       
        // If empty, return "0"
        return ans.empty() ? "0" : ans;
    }
};


/*
==================== APPROACH ====================

👉 Core Idea: Greedy + Monotonic Increasing Stack

We want the smallest possible number after removing k digits.

1. Think of ans as a stack:
   - Maintain digits in increasing order.
   - If a new digit is smaller than the top → remove the top (if k > 0).

2. Why greedy works?
   - Bigger digit on left contributes more to value.
   - So removing it early reduces overall number significantly.

3. Leading Zero Handling:
   - Avoid pushing '0' if ans is empty.
   - Prevents cases like "00200".

4. Remaining k:
   - If k still > 0 after loop → remove from end
   - Because remaining digits are already increasing.

5. Edge Case:
   - If everything removed → return "0"

--------------------------------------------------

⏱ Time Complexity: O(n)
- Each digit is pushed once and popped at most once

📦 Space Complexity: O(n)
- Stack (ans string) can hold up to n characters

==================================================
*/
