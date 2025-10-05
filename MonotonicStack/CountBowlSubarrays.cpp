class Solution {
public:
    
    vector<int> previousGreaterElement(vector<int>& a)
    {
        int n = a.size();
        vector<int>ans(n,-1);
        stack<int>stk; 
        // mainitain mono decreasing
        for(int i=0;i<n;i++)
        {
            while(!stk.empty() and a[stk.top()]<=a[i])
            {
                stk.pop();
            }
            // current value of stack is prev greater of current i
            if(!stk.empty())
                ans[i] = stk.top();
            stk.push(i);
        }
        for(auto xt : ans)
            cout<<xt<<" ";
        return ans;
    }

        vector<int> nextGreaterElement(vector<int>& a)
    {
        int n = a.size();
        vector<int>ans(n,n);
        stack<int>stk; 
        // mainitain mono decreasing
        for(int i=0;i<n;i++)
        {
            while(!stk.empty() and a[stk.top()] < a[i])
            {
                // current value i is next greater element of all previous indexes in stack
                ans[stk.top()] = i;
                stk.pop();

            }
            stk.push(i);
        }
        for(auto xt : ans)
            cout<<xt<<" ";
        return ans;
    }

    long long bowlSubarrays(vector<int>& a)
    {
        vector<int>previousGreater = previousGreaterElement(a);

        vector<int>nextGreater = nextGreaterElement(a);

        long long ans=0;
        int n = a.size();
        for(int i=0;i<n;i++)
        {
            if(previousGreater[i]!=-1 && nextGreater[i]!=n)
            {
                ans++;
            }
        }
        return ans;
    }
};

/*
APPROACH:
1. For each element, we find:
   - previous greater element on the left (using a decreasing stack)
   - next greater element on the right (using a decreasing stack)

2. previousGreaterElement():
   - Iterate left → right
   - Pop all elements smaller/equal to current
   - Top of stack (if exists) is previous greater
   - Push current index

3. nextGreaterElement():
   - Iterate left → right
   - While current > top, current is next greater of stack’s top
   - Pop and assign, then push current index

4. bowlSubarrays():
   - For every element, if both previous and next greater exist,
     we count it as a valid “bowl” subarray point.

Time Complexity:  O(n)
Space Complexity: O(n)
*/
