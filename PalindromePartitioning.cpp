class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> path;
        dfs(s, 0, ans, path);  // Start DFS from index 0
        return ans;
    }
    
    void dfs(string &s, int index, vector<vector<string>>& ans, vector<string>& path) {
        if (index == s.length()) {
            ans.push_back(path);  // Add current path to the result
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (ispali(s, index, i)) {  // Check if substring is palindrome
                path.push_back(s.substr(index, i - index + 1));  // Add palindrome to path
                dfs(s, i + 1, ans, path);  // Recurse for next substring
                path.pop_back();  // Backtrack
            }
        }
    }
    
    bool ispali(string &s, int start, int end) {
        while (start <= end) {
            if (s[start] != s[end]) {
                return false;  // Not a palindrome
            }
            start++;
            end--;
        }
        return true;  // Is a palindrome
    }
};
