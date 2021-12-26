class Solution {
public:
     bool havingSameFrequency(int a[] , int b[]){
       
        for(int i=0;i<26;i++){
            if(a[i]!=b[i])
                return false;
        }
        return true;
    }
    bool checkInclusion(string aa, string bb) {
        int l1 = aa.length();
        int l2 = bb.length();
        if(l1>l2) return false;
        int aa1[26]={0};
        int bb1[26]={0};
        for(int i=0;i<l1;i++){
            aa1[aa[i]-'a']++;
            bb1[bb[i]-'a']++;
        }
        if(havingSameFrequency(aa1,bb1)) return true;
        for(int i=l1;i<l2;i++){
            bb1[bb[i]-'a']++;
            bb1[bb[i-l1]-'a']--;
            if(havingSameFrequency(aa1,bb1)) return true;
        }
        return false;
    }
};
