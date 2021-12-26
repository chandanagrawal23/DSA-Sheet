class Solution {
public:
    int numberOfSubstrings(string s) {
        int count[3] = {0, 0, 0};
           int res = 0 , i = 0, n = s.length();
        for (int j = 0; j < n; ++j) {
            ++count[s[j] - 'a'];
            while (count[0] && count[1] && count[2])
            {
                res += (n-j);
                count[s[i] - 'a']--;
                i++;
            }
        }
        return res;
        
    }
};
