class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) 
    {
        int n = s.size();
        vector<vector<int>> prefix(n + 1, vector<int>(26, 0));
        
        // Build 2D prefix sum array
        for (int i = 0; i < n; i++) 
        {
            prefix[i + 1] = prefix[i]; // copy previous counts
            prefix[i + 1][s[i] - 'a']++; // increment current char
        }

        vector<bool> ans;
        for (auto &q : queries) 
        {
            int l = q[0], r = q[1], k = q[2];
            
            // Count odd frequency letters
            int oddCount = 0;
            for (int ch = 0; ch < 26; ch++) 
            {
                int cnt = prefix[r + 1][ch] - prefix[l][ch];
                if (cnt % 2 != 0) 
                    oddCount++;
            }

            // Need oddCount / 2 replacements to make palindrome
            if((oddCount / 2) <= k)
              ans.push_back(true);
            else
              ans.push_back(false);
        }
        return ans;
    }
};
/* 
APPROACH:
We want to check for each query [l, r, k] whether substring s[l..r] 
can be converted into a palindrome with at most k character replacements.

1. Precompute a 2D prefix frequency array `prefix[i][ch]`:
   - prefix[i][ch] = number of times character 'a'+ch appears 
     in s[0..i-1].
   - This allows us to get frequency of any character in O(1) for 
     any substring:
       count(ch, l, r) = prefix[r+1][ch] - prefix[l][ch].

2. For each query:
   a) Find frequency of all 26 characters in substring s[l..r].
   b) Count how many have odd frequency → oddCount.
   c) In a palindrome, at most 1 char can have odd frequency.
      To fix oddCount > 1, we need (oddCount / 2) replacements.
   d) If (oddCount / 2) <= k → push true, else push false.

   WHY ?? (oddCount / 2) <= k
    
    Suppose in range [l,r] we have 5 char's whose frequency is ODD
    A 3
    B 5
    C 7
    D 3
    E 9
    
    Now in one operation I can make two char's as even HOW ? 
    
    Change 1A to 1B so A = 2 , B = 6
    same 1C to 1D so C = 6 , D = 3
    E = 9  which is ok, as in plaindrom we have at most 1 char whose frequency is ODD
    So total operatio is 5/2 = 2 if 2 <=k then we are OK otherwise not possible

Example:
s = "abcda", query = [0,4,1]
freq: a=2,b=1,c=1,d=1 → oddCount=3
needed = 3/2=1, k=1 → possible.

Time Complexity:
- Prefix build: O(n * 26)
- Each query: O(26)
Space Complexity: O(n * 26)
*/
