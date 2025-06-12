// using DFS
class Solution
{
public:
    void solve(vector<vector<char>>& board)
    {
        if (board.empty()) return;

        int rows = board.size();
        int cols = board[0].size();

        // Step 1: Mark all border-connected 'O's as '$'
        for (int i = 0; i < rows; ++i)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);              // Left border
            if (board[i][cols - 1] == 'O')
                dfs(board, i, cols - 1);       // Right border
        }

        for (int j = 0; j < cols; ++j)
        {
            if (board[0][j] == 'O')
                dfs(board, 0, j);              // Top border
            if (board[rows - 1][j] == 'O')
                dfs(board, rows - 1, j);       // Bottom border
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // Step 2: Convert remaining 'O' to 'X' (surrounded)
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                // Step 3: Convert '$' back to 'O' which are bordered one
                else if (board[i][j] == '$')
                    board[i][j] = 'O';
            }
        }
    }

    // DFS to mark border-connected 'O's as '$'
    void dfs(vector<vector<char>>& board, int i, int j)
    {
        int rows = board.size();
        int cols = board[0].size();

        if (i < 0 || j < 0 || i >= rows || j >= cols || board[i][j] != 'O')
            return;

        board[i][j] = '$';  // Mark as part of a border-connected region

        dfs(board, i - 1, j);  // Up
        dfs(board, i + 1, j);  // Down
        dfs(board, i, j - 1);  // Left
        dfs(board, i, j + 1);  // Right
    }
};

/*
Approach:
- Mark all 'O's connected to any border as '$' (safe).
- Then convert all other internal 'O's to 'X' (surrounded).
- Finally, convert all '$' back to 'O'.

Time Complexity: O(m * n) — Every cell is visited at most once.
Space Complexity: O(m * n) — Recursion stack space for DFS.
*/


//==========================================================================================================================================================

// using BFS 


#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    void solve(vector<vector<char>>& board)
    {
        if (board.empty())
            return;

        int rows = board.size();
        int cols = board[0].size();
        queue<pair<int, int>> q;

        // Step 1: Mark all border-connected 'O's using BFS
        for (int i = 0; i < rows; ++i)
        {
            if (board[i][0] == 'O')
                q.push({i, 0});
            if (board[i][cols - 1] == 'O')
                q.push({i, cols - 1});
        }

        for (int j = 0; j < cols; ++j)
        {
            if (board[0][j] == 'O')
                q.push({0, j});
            if (board[rows - 1][j] == 'O')
                q.push({rows - 1, j});
        }

        // Perform BFS and mark all connected 'O's as '$'
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x < 0 || y < 0 || x >= rows || y >= cols || board[x][y] != 'O')
                continue;

            board[x][y] = '$';

            q.push({x - 1, y});  // Up
            q.push({x + 1, y});  // Down
            q.push({x, y - 1});  // Left
            q.push({x, y + 1});  // Right
        }

        // Step 2: Convert internal 'O's to 'X', and border '$' back to 'O'
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '$')
                    board[i][j] = 'O';
            }
        }
    }
};

/*
Approach:
- Use BFS to mark all 'O's connected to the border as '$'.
- After BFS, all remaining 'O's are surrounded → flip to 'X'.
- Finally, change all '$' back to 'O'.

Time Complexity: O(m * n) — Every cell is visited at most once.
Space Complexity: O(m * n) — Space for queue in BFS.
*/


