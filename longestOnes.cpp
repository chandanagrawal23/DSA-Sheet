class Solution {
public:
    int longestOnes(vector<int>& a, int k) {
        int n = a.size();
        int left = 0 ;
        int maxi = -1;
        int zero=0;
        for(int right = 0 ;right<n;right++)
        {
            if(a[right]==0)
                zero++;
            while(zero>k)
            {
                if(a[left]==0)
                    zero--;
                left++;
            }
            maxi = max(maxi , right-left+1);
        }
        return maxi;
    }
};

//Find the longest subarray with at most K zeros
