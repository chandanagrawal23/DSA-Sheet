class Solution {
public:
    int characterReplacement(string s, int k) {
        int maxi = -1;
        for(char ch = 'A';ch<='Z';ch++)
        {
            maxi = max(maxi , allCH(s,k,ch));
        }
        return maxi ; 
    }
    
    // longest string with atmost k non ch's
    int allCH(string a , int k,char ch)
    {
        int n = a.size();
        int left = 0 ;
        int maxi = -1;
        int b=0;
        for(int right = 0 ;right<n;right++)
        {
            b+=(a[right]!=ch);
            while(b>k)
            {
                b-=(a[left++]!=ch);
            }
            maxi = max(maxi , right-left+1);
        }
        return maxi;
    }
};
