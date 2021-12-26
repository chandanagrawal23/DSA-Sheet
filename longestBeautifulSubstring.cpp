class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int maxLen = 0;
        for (int i = 1; i < word.size(); i++) {
            if (word[i-1] == 'a') {
                int currLen = 1, uniqueChars = 1;
                // word[i-1] -> prev char
                // word[i] -> curr char
                while (i < word.size() && word[i-1] <= word[i]) {
                    if(word[i-1]<word[i])
                        uniqueChars +=1;
                    currLen++;
                    i++;
                }
                if (uniqueChars == 5) 
                    maxLen = max(maxLen, currLen);
            }
        }
        return maxLen;
        
        
        // below approach take bit extra time , we have to check which start from 'a'
//         const auto n = word.size();

//         int cnt = 1;
//         int len = 1;
//         int max_len = 0;
//         for (int i = 1; i != n; ++i) {
//             if (word[i - 1] == word[i]) {
//                 ++len;
//             } else if (word[i - 1] < word[i]) {
//                 ++len;
//                 ++cnt;
//             } else {
//                 cnt = 1;
//                 len = 1;
//             }
            
//             if (cnt == 5) {
//                 max_len = max(max_len, len);
//             }
//         }
//         return max_len;
        
        
    }
};

//The basic idea is 'a' < 'e' < 'i' < 'o' < 'u'. So this problem is to find the length of the longest non-decreasing substring that has five different chars.

// also string contain only vowels so it is easy
