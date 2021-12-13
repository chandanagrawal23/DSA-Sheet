class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<int> st;
        int cnt =0;
        for (auto i = 0; i < s.size(); ++i) {
        if (s[i] == '(') st.push(i);
        if (s[i] == ')') {
          if (!st.empty())
            st.pop();
          else
            cnt++;
        }
      }
      return cnt + st.size();
    }
};
