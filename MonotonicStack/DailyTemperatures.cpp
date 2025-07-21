class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& a) {
        stack<pair<int,int>>st;
        int n = a.size();
        vector<int>ans(n,0);

        for(int i=n-1;i>=0;i--)
        {
            while(!st.empty() and a[i]>=st.top().first)
            {
                st.pop();
            }
            ans[i] = (st.empty() ? 0 : st.top().second-i);
            st.push({a[i],i});
        }
        return ans;
    }
};
