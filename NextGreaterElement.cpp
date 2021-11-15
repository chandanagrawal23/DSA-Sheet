//https://practice.geeksforgeeks.org/problems/next-larger-element-1587115620/1#
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find the next greater element for each element of the array.
    vector<long long> nextLargerElement(vector<long long> a, int n){
        stack<long long >st;
        vector<long long>ans(n,0);

        for(long long i=n-1;i>=0;i--)
        {
            while(!st.empty() and a[i]>=st.top())
            {
                st.pop();
            }
            ans[i] = (st.empty() ? -1 : st.top());
            st.push(a[i]);
        }
        return ans;
    }
};
