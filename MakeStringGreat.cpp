class Solution {
public:
    string makeGood(string s) {
        stack<char> stk;
        string op;
        for(auto a: s)
        {
            if(!stk.empty() && abs(stk.top() - a) == 32)
                stk.pop();
            else
                stk.push(a);
        }
        while(!stk.empty())
        {
            op.push_back(stk.top());
            stk.pop();
        }
        reverse(op.begin(),op.end());
        return op;
    }
};
