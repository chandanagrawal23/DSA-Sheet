class Solution
{
public:
    int longestValidParentheses(string s)
    {
        stack<int> stk;
        stk.push(-1); // Base for the first valid substring
        int ans = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                // Push the index of '('
                stk.push(i);
            }
            else
            {
                // Pop the last unmatched '(' or a previous base
                stk.pop();

                if (stk.empty())
                {
                    // If stack becomes empty, push current index as new base
                    stk.push(i);
                }
                else
                {
                    // Valid substring found, update max length
                    ans = max(ans, i - stk.top());
                }
            }
        }

        return ans;
    }
};

/*

🔍 Approach Explanation:

- We use a stack to store **indices**, not characters.
- Start by pushing `-1` to serve as the base for the first valid substring.
- For every `'('`, push its index to the stack.
- For every `')'`:
  - Pop the top.
  - If stack becomes empty → push current index (to reset base).
  - If not empty → length of current valid substring = `i - stk.top()`.

📌 Why push -1 initially?
To handle cases like `"()"`, where the valid substring starts at index 0.

💡 Time Complexity: O(n)  
💡 Space Complexity: O(n)

*/
