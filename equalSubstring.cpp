class Solution {
public:
       int equalSubstring(string s, string t, int k) {
           
           int n = s.length(), i = 0, j;
           int maxi = 0;
           int sum = 0;
            for (j = 0; j < n; ++j) {
                sum += abs(s[j] - t[j]);
                while(sum>k)
                {
                    sum -=  abs(s[i] - t[i]);
                    i++;
                }
                maxi = max(maxi , j-i+1);
            }
            return maxi;    
    }
};
