//https://leetcode.com/problems/asteroid-collision/
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& a) {
        stack<int>st;
        for(int val  : a)
        {
            if(val>0)
                st.push(val);
            else
            {
                while(!st.empty() and st.top()>0 and st.top()<abs(val))
                    st.pop();
                if(!st.empty() and st.top()==abs(val))
                    st.pop();
                else
                {
                     if(st.empty() || st.top() < 0) 
                        st.push(val);
                }
            }
        }
        
        vector<int>ans;
        while(!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(),ans.end());
        return ans;
        
    }
};
