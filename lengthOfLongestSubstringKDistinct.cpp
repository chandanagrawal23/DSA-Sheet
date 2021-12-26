class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        map<char,int>mp;
        int l = 0 , n = s.size() , r=0 ,ans = -1;
        while(r<n)
        {
            mp[s[r]]++;
            while(mp.size()>k)
            {
                mp[s[l]]--;
                if(mp[s[l]]==0)
                    mp.erase(s[l]);
                l++;
            }
            ans = max(ans , r-l+1);
            r++;
        }
        return ans;
    }
};
