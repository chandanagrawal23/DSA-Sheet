class Solution {
public: 
    int similarPairs(vector<string>& words) {
        int ans = 0; 
        unordered_map<int, int> freq;  // Stores frequency of each unique bitmask

        // Step 1: Convert each word to a bitmask representing its unique characters
        for (auto& word : words) {
            int mask = 0; 
            for (auto& c : word) 
                mask |= 1 << (c - 'a');  // Set the bit corresponding to character c
            freq[mask]++;  // Count how many times each mask appears
        }

        // Step 2: Count pairs of words with the same mask using combination nC2
        for (auto& [mask, count] : freq) {
            if (count > 1)
                ans += (count * (count - 1)) / 2;
        }

        return ans; 
    }
};

/*
Approach:

Here instead of storing the substring , we are storing the hash for each uniq char, the best way is masking for each char.

- Convert each word into a 26-bit mask where each bit represents presence of a character.
- Store the frequency of each unique bitmask in a hash map.
- If two words have the same bitmask, they contain the same set of characters.
- For each bitmask with frequency > 1, count the number of valid pairs using nC2 = (n * (n - 1)) / 2.

✅ Time: O(n * m), where n = number of words, m = max length of a word  
✅ Space: O(1) (since max 2^26 masks), practically bounded
*/
