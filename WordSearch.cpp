class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Start DFS if first letter matches
                if (word[0] == board[i][j] && dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int x) {
        // If we've matched all characters in the word
        if (x == word.length())
            return true;
        
        // Boundary checks and character mismatch
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != word[x])
            return false;
        
        char temp = board[i][j];  // Save current character

       //set
        board[i][j] = '#';  // Mark as visited by setting it to an invalid character
        
        // Explore all four possible directions (up, down, left, right)
        if (dfs(board, word, i + 1, j, x + 1) || 
            dfs(board, word, i - 1, j, x + 1) || 
            dfs(board, word, i, j + 1, x + 1) || 
            dfs(board, word, i, j - 1, x + 1)) {
            return true;
        }
        
        // Backtrack: reset the cell to its original value
        board[i][j] = temp;
        
        return false;
    }
};
