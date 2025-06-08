class Solution {

    // Recursive function to simulate the ball's path starting at (i, j)
    int solve(int i, int j, vector<vector<int>>& arr,int n, int m) {
        // If ball has reached beyond the last row, return current column as final position
        if (i >= n) return j;

        // Check if current board cell is directing ball to the right (1)
        // and next cell in same row to the right is also 1 (forming a valid slope)
        if (arr[i][j] == 1 && j + 1 < m && arr[i][j + 1] == 1) {
            // Move ball diagonally right-down
            return solve(i + 1, j + 1, arr, n, m);
        }
        // Check if current board cell is directing ball to the left (-1)
        // and next cell in same row to the left is also -1 (valid slope)
        else if (arr[i][j] == -1 && j - 1 >= 0 && arr[i][j - 1] == -1) {
            // Move ball diagonally left-down
            return solve(i + 1, j - 1, arr, n, m);
        }
        // Ball gets stuck (V-shape or boundary), no valid path
        else
            return -1;
    }

public:
    vector<int> findBall(vector<vector<int>>& arr) {
        int n = arr.size();
        int m = arr[0].size();

        vector<int> ans(m);
        // Start ball drop simulation from each column in the top row
        for (int i = 0; i < m; i++) {
            ans[i] = solve(0, i, arr, n, m);
        }
        return ans;
    }
};


/*
Short Notes:
- The solve() function recursively tracks the ball's position moving diagonally down-left or down-right.
- If the ball reaches the bottom, it returns the final column.
- If ball hits boundary or forms a V-shape, returns -1.
- This is done for each starting column.

Time Complexity: O(n * m) 
  - Each cell is visited at most once per ball drop; 
  - There are m balls dropped, and each path has length n.

Space Complexity: O(n) due to recursion stack depth (max rows).
*/
