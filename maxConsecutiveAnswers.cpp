class Solution {
public:
    int maxConsecutiveAnswers(string s, int k) {
        return max(longestTrue(s,k),longestFalse(s,k));
    }
    // at most "k" false allowed
    int longestTrue(string a, int k) {
        int n = a.size();
        int left = 0 ;
        int maxi = -1;
        int False=0;
        for(int right = 0 ;right<n;right++)
        {
            False+=(a[right]=='F');
            while(False>k)
            {
                False-=(a[left++]=='F');
            }
            maxi = max(maxi , right-left+1);
        }
        return maxi;
    }
    
    // at most "k" True allowed
    int longestFalse(string a, int k) {
        int n = a.size();
        int left = 0 ;
        int maxi = -1;
        int True=0;
        for(int right = 0 ;right<n;right++)
        {
            True+=(a[right]=='T');
            while(True>k)
            {
                True-=(a[left++]=='T');
            }
            maxi = max(maxi , right-left+1);
        }
        return maxi;
    }
};
