class Solution {
public:
    bool isValid(string s) {
        stack<char>st;
        // map the bracket , in dictionary
        map<char,char>mp;
        mp[')']='(';
        mp['}']='{';
        mp[']']='[';
        
        for(char currBracket : s)
        {
            if(currBracket=='(' or currBracket=='{' or currBracket == '[')
                st.push(currBracket);
            else
            {
                if(!st.empty() and st.top()!=mp[currBracket])
                    return false;
                if(!st.empty() and st.top()==mp[currBracket])
                    st.pop();
                else if(st.empty())
                    st.push(currBracket);
            }
        }
        return st.empty();
    }
};
