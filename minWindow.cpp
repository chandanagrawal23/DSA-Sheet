class Solution {
public:
    /*
    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();
        int left = 1 , right = n;
        int ans = -1;
        while(left<right)
        {
            int mid = (left + right)/2;
            if(possible(s , t , mid))
            {
                ans = mid ; 
                right = mid-1;
            }
            else
            {
                left = mid;
            }
        }
        return ans;
    }
    
    bool possible(string &s , string &t , int len)
    {
        map<char,int>mp1 , mp2;
        for(auto xt : t)
            mp2[xt]++;
        for(int i=0;i<len;i++)
        {
            mp1[s[i]]++;
        }
        if(check(mp1,mp2))
            return true;
        for(int i=len;i<s.size();i++)
        {
            mp1[s[i]]++;
            mp1[s[i-len]]--;
            if(check(mp1,mp2))
                return true;
        }       
        return false;
    }
    
    bool check(map<char,int>&a , map<char,int>&b)
    {
        for(auto xt : b)
        {
            if(a.find(xt.first)==a.end())
                return false;
        }
        return true;
    }*/
    
    string minWindow(string s, string t) {
        int n = s.size();
        unordered_map<char,int>mpT;
        for(auto xt : t)
            mpT[xt]++;
        int req = mpT.size();
        map<char,int>window;
        int found = 0;
        int minilen = INT_MAX;
        int start , end;
        int left = 0 ,  right = 0;
        while(right<n)
        {
            window[s[right]]++;
            if(mpT.find(s[right])!=mpT.end() and window[s[right]]==mpT[s[right]])
                found++;
            
            while(left<=right and found==req)
            {
                if((right-left+1)<minilen)
                {
                    minilen = (right-left+1);
                    start = left;
                    end = right;
                }
                window[s[left]]--;
                if(mpT.find(s[left])!=mpT.end() and window[s[left]]<mpT[s[left]])
                    found--;
                left++;
            }
            right++;
        }
        if(minilen==INT_MAX)
            return "";
        return s.substr(start,end-start+1);
    }
};
