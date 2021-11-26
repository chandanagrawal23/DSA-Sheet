//https://leetcode.com/problems/remove-k-digits/
class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans = "";   // treat ans as a stack in below for loop
        stack<char> st;
       
       for (char c : num)
       {
           while (!st.empty() && st.top() > c && k>0) {
               st.pop(); // make sure digits in ans are in ascending order
               k--;   // remove one char
           }
           
           if (!st.empty() || c != '0') { // can't have leading '0'
               st.push(c);
           }  
       }
       
       while (!st.empty() && k>0) { // make sure remove k digits in total
           st.pop(); 
           k--;
       }    
        if(st.empty())
            return "0";
        else
            string ans = "";
        while (!st.empty()) { // make sure remove k digits in total
           ans = st.top()+ans;
            st.pop();
       }
       return ans;
    }
};
