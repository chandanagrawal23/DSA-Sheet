class Solution {
public:
    int numSub(string s) {
        long long right = 0;
        long long left = 0;
        long long n = s.size();
        long long countTotalZeroes = 0;
        long long  ans = 0;
        while(right<n)
        {
            countTotalZeroes+=(s[right]=='0');
            while(countTotalZeroes>0)
            {
                countTotalZeroes-=(s[left]=='0');
                left++;
            }
            ans = (ans%1000000007 + (right-left+1)%1000000007)%1000000007;
            right++;
        }
        return ans;
    }
};
