class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        if (words.empty() || letters.empty() || score.empty()) return 0;

        vector<int> count(26, 0);  // To count available letters
        for (char ch : letters) {
            count[ch - 'a']++;
        }

        return backtrack(words, count, score, 0);
    }

private:
    int backtrack(vector<string>& words, vector<int>& count, vector<int>& score, int index) {
        int maxScore = 0;

        for (int i = index; i < words.size(); ++i) {
            bool isValid = true;
            int res = 0;
            vector<int> used(26, 0);  // Track how many times we use each letter in this word

            for (char ch : words[i]) {
                int idx = ch - 'a';
                used[idx]++;
                res += score[idx];
                if (used[idx] > count[idx]) {
                    isValid = false;
                }
            }

            if (isValid) {
                // Deduct used letters from count
                for (int j = 0; j < 26; ++j) {
                    count[j] -= used[j];
                }

                res += backtrack(words, count, score, i + 1);
                maxScore = max(maxScore, res);

                // Restore count
                for (int j = 0; j < 26; ++j) {
                    count[j] += used[j];
                }
            }
        }

        return maxScore;
    }
};
