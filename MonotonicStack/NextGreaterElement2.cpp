class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& a) {
        stack<int> s;
        int n = a.size();
        vector<int>res(n,-1);
        for (int i=0;i<2*n;i++) {
            int val = a[i%n];
            while (s.size() && a[s.top()] < val) {
                res[s.top()] = val;
                s.pop();
            }
            if(i<n)
                s.push(i);
        }
        return res;
    }
};

//https://leetcode.com/problems/next-greater-element-ii/
