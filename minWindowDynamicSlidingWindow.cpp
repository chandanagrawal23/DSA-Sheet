class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        
        // Frequency map of characters in t
        unordered_map<char,int> mpT;
        for(auto ch : t)
            mpT[ch]++;
        
        int req = mpT.size();  // Number of unique characters needed
        map<char,int> window;  // Current window character frequency
        int found = 0;         // Number of characters matched with required freq
        
        int minilen = INT_MAX; // Minimum window length found
        int start, end;        // Start and end indices of the minimum window
        int left = 0, right = 0;

        while(right < n)
        {
            // Expand the window by including s[right]
            window[s[right]]++;

            // If current char count matches with t's requirement, increase found
            if(mpT.find(s[right]) != mpT.end() && window[s[right]] == mpT[s[right]])
                found++;
            
            // Try shrinking the window from the left while all required characters are found
            while(left <= right && found == req)
            {
                // Update the result if this window is smaller than previous best
                if((right - left + 1) < minilen)
                {
                    minilen = right - left + 1;
                    start = left;
                    end = right;
                }

                // Shrink from the left
                window[s[left]]--;
                if(mpT.find(s[left]) != mpT.end() && window[s[left]] < mpT[s[left]])
                    found--;
                left++;
            }

            // Move right pointer to expand window
            right++;
        }

        // If no valid window found, return empty string
        if(minilen == INT_MAX)
            return "";

        return s.substr(start, end - start + 1);
    }
};

/*
-----------------------------------------------
🧠 Short Approach:

1. Use two pointers (sliding window) to expand and shrink the window.
2. Maintain two hash maps:
   - mpT: character frequency required from string `t`
   - window: current window character frequency
3. Expand window by moving `right`. When all required chars match in freq, try shrinking from `left`.
4. Update minimum window length and position if a smaller valid window is found.
5. Finally, return the minimum window substring.

🕒 Time Complexity: O(N) — each character is visited at most twice
💾 Space Complexity: O(1) — since the alphabet size is constant (max 128/256)
-----------------------------------------------
*/
