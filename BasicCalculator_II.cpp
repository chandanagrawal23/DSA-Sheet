//https://leetcode.com/problems/basic-calculator-ii/
class Solution {
public:
    int calculate(string s) {
        int len = s.length();
        if (len == 0) return 0;
        stack<int> stack;
        int currentNumber = 0;
        char lastoperation = '+';
        for (int i = 0; i < len; i++)
        {
            char currentChar = s[i];
            
            if (isdigit(currentChar))
            {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
            
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == len - 1) 
            {
                if (lastoperation == '-') 
                {
                    stack.push(-currentNumber);
                } 
                else if (lastoperation == '+') 
                {
                    stack.push(currentNumber);
                } 
                else if (lastoperation == '*') 
                {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop * currentNumber);
                } 
                else if (lastoperation == '/')
                {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop / currentNumber);
                }
                lastoperation = currentChar;
                currentNumber = 0;
            }
        }
        
        int result = 0;
        
        while (stack.size() != 0) 
        {
            result += stack.top();
            
            stack.pop();
        }
        return result;
    }
};
