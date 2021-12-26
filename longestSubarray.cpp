class Solution {
public:
    int longestSubarray(vector<int>& a) {
        int left = 0;
        int zero  = 0;
        int ans = 0;
        int n  = a.size();
        for(int right=0;right<n;right++)
        {
            zero+=(a[right]==0);
            while(zero>1)
            {
                zero-=(a[left]==0);
                left++;
            }
            ans = max(ans,right-left); // we have to delete 1 element guranteed that is why inseatad of r-l+1 we wrote r-l
        }
        return ans;
        
    }
};

// this is similar like atmost 1 (k=1 )  "0" are allowed
