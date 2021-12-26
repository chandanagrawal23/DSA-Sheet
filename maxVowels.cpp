bool isvowel(char ch) {
    // return (0x208222>>(v&0x1f))&1;
    string str = "aeiouAEIOU";
    return (str.find(ch) != string::npos);
}
class Solution {
public:
    int maxVowels(string s, int k) {
        int cnt=0;
        for(int i=0;i<k;i++){
            if(isvowel(s[i])) cnt++;
        }
        int maxi=0;
        maxi = max(maxi,cnt);
        for(int i=k;i<s.length();i++){
            if(isvowel(s[i]))
                 cnt++;
            if(isvowel(s[i-k]))
                  cnt--;
            maxi = max(maxi,cnt);
        }
        return maxi;
    }
};
