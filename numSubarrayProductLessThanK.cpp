class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& a, int k) {
        if(k==0)
            return 0;
        long long int left =  0;
        long long int right = 0 , n = a.size();
        long long int pro = 1,ans=0;
        while(right<n)
        {
            pro *= a[right];
            while(left<=right and pro>=k)
            {
                pro/=a[left++];
            }
            ans += (right-left+1);
            right++;
        }
        return ans;
    }
};
