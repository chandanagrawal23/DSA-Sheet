class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        map<char, int> mp;  // Stores character frequency in current window
        int l = 0, r = 0, n = s.size(), ans = -1;

        // Iterate through the string using right pointer `r`
        while (r < n) {
            mp[s[r]]++;  // Add character s[r] to map (or increment count)

            // If number of distinct characters exceeds k, shrink window from left
            while (mp.size() > k) {
                mp[s[l]]--;  // Decrease count of character at left pointer
                if (mp[s[l]] == 0)
                    mp.erase(s[l]);  // Remove it from map if count becomes 0
                l++;  // Move left pointer to right
            }

            // Update maximum length found so far
            ans = max(ans, r - l + 1);

            r++;  // Move right pointer to expand window
        }

        return ans;
    }
};
