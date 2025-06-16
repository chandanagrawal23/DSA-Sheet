class Solution {
public:
    int solve(int index, vector<vector<int>> &books, int shelfWidth, vector<int> &dp)
    {
        if (index >= books.size())
            return 0;

        if (dp[index] != -1)
            return dp[index];

        int currWidth = 0;
        int maxHeight = 0;
        int ans = INT_MAX;

        for (int i = index; i < books.size(); i++)
        {
            int bookWidth = books[i][0];
            int bookHeight = books[i][1];

            if (currWidth + bookWidth > shelfWidth)
                break; // can't fit this book in the current shelf

            currWidth += bookWidth;
            maxHeight = max(maxHeight, bookHeight); // update shelf height if needed

            // Try placing books from index to i in the current shelf
            ans = min(ans, maxHeight + solve(i + 1, books, shelfWidth, dp));
        }

        return dp[index] = ans; // store and return the result for current index
    }

    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        vector<int> dp(books.size(), -1); // dp[i] stores min height from i to end
        return solve(0, books, shelfWidth, dp);
    }
};

/*
Approach:
- At each index, try placing books [index to i] on the current shelf as long as the total width <= shelfWidth.
- Track:
   → currWidth = total width of books in the current shelf
   → maxHeight = height of the current shelf (max of all book heights in it)
- Recurse for remaining books from i+1 onward, and add maxHeight to the result.
- Return the minimum total height by trying all valid splits.
- Use memoization (dp) to store results for subproblems to avoid recomputation.

Example:
books = [[1,3],[2,4],[3,2]], shelfWidth = 6

Choices:
- Place all on one shelf: totalWidth = 6, maxHeight = 4 → total height = 4
- Or split: [[1,3],[2,4]] + [[3,2]] → heights = 4 + 2 = 6 → worse

Time Complexity: O(N^2), as for each index we may scan up to N
Space Complexity: O(N), for dp
*/
