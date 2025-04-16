class Solution {
public:
    int partitionString(string &s) {
        int n = s.size();
        int i = 0;
        int cnt = 0; // Count of partitions (substrings with all unique characters)

        while (i < n) {
            int a[26] = {0}; // Frequency array to track characters in current partition

            // Expand the current partition until a duplicate character is found
            while (i < n && a[s[i] - 'a'] == 0) {
                a[s[i] - 'a']++; // Mark character as seen
                i++;             // Move to next character
            }

            // One valid partition (with unique characters) is completed
            cnt++;
        }

        return cnt; // Total number of such partitions
    }
};
