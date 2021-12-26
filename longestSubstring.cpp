class Solution {
public:
    int longestSubstring(string s, int k) {
        int countMap[26];
        set<char> totaluniq(s.begin(),s.end());
        int maxUnique = totaluniq.size();
        int result = 0;
        for (int currUnique = 1; currUnique <= maxUnique; currUnique++) {
            // reset countMap
            memset(countMap, 0, sizeof(countMap));
            int windowStart = 0, windowEnd = 0, idx = 0, unique = 0, countAtLeastK = 0;
            while (windowEnd < s.size()) {
                // expand the sliding window
                if (unique <= currUnique) {
                    idx = s[windowEnd] - 'a';
                    if (countMap[idx] == 0) unique++;
                    countMap[idx]++;
                    if (countMap[idx] == k) countAtLeastK++;
                    windowEnd++;
                }
                // shrink the sliding window
                else {
                    idx = s[windowStart] - 'a';
                    if (countMap[idx] == k) countAtLeastK--;
                    countMap[idx]--;
                    if (countMap[idx] == 0) unique--;
                    windowStart++;
                }
                if (unique == currUnique && unique == countAtLeastK)
                    result = max(windowEnd - windowStart, result);
            }
        }

        return result;
    }
};

/*

Approach 3: Sliding Window
Intuition

There is another intuitive method to solve the problem by using the Sliding Window Approach. The sliding window slides over the string s and validates each character. Based on certain conditions, the sliding window either expands or shrinks.

A substring is valid if each character has at least k frequency. The main idea is to find all the valid substrings with a different number of unique characters and track the maximum length. Let's look at the algorithm in detail.

Algorithm

Find the number of unique characters in the string s and store the count in variable maxUnique. For s = aabcbacad, the unique characters are a,b,c,d and maxUnique = 4.

Iterate over the string s with the value of currUnique ranging from 1 to maxUnique. In each iteration, currUnique is the maximum number of unique characters that must be present in the sliding window.

The sliding window starts at index windowStart and ends at index windowEnd and slides over string s until windowEnd reaches the end of string s. At any given point, we shrink or expand the window to ensure that the number of unique characters is not greater than currUnique.

If the number of unique character in the sliding window is less than or equal to currUnique, expand the window from the right by adding a character to the end of the window given by windowEnd

Otherwise, shrink the window from the left by removing a character from the start of the window given by windowStart.

Keep track of the number of unique characters in the current sliding window having at least k frequency given by countAtLeastK. Update the result if all the characters in the window have at least k frequency.



*/
