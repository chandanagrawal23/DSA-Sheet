//https://leetcode.com/problems/buildings-with-an-ocean-view/
class Solution {
public:
    vector<int> findBuildings(vector<int>& a) {
        int n = a.size();
        stack<int  >st;
        vector<int >ans;

        for(int i=n-1;i>=0;i--)
        {
            while(!st.empty() and a[i]>st.top())
            {
                st.pop();
            }
            if(st.empty())
                ans.push_back(i);
            st.push(a[i]);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
