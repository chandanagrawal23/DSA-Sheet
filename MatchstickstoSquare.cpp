class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        // If no. of matchsticks are less than 4, then cannot form square.
        if (matchsticks.size() < 4) {
            return false;
        }

        // Calculate sum of length of every stick.
        int sum = 0;
        for (int stick : matchsticks) {
            sum += stick;
        }

        // Every side of square should have the same length, so overall sum should be divisible by 4
        if (sum % 4 != 0) {
            return false;
        }

        // Calculate the length of one side of the square
        int sideLen = sum / 4;
        
        // Sort matchsticks in descending order for optimization (helps with pruning in DFS)
        sort(matchsticks.rbegin(), matchsticks.rend());

        // Call the DFS function with 4 sides initially set to 0
        return dfs(0, 0, 0, 0, matchsticks, 0, sideLen);
    }

private:
    // DFS function to return if the sides can form a square
    bool dfs(int s1, int s2, int s3, int s4, vector<int>& arr, int k, int len) {
        // If any side exceeds the required side length, return false
        if (s1 > len || s2 > len || s3 > len || s4 > len) {
            return false;
        }

        // If all matchsticks are used (i.e., index reaches the end)
        if (k == arr.size()) {
            // If all sides are equal, return true (this means a square is formed)
            return s1 == s2 && s2 == s3 && s3 == s4;
        }

        // Try adding the current matchstick to each of the four sides
        return (dfs(s1 + arr[k], s2, s3, s4, arr, k + 1, len) ||
                dfs(s1, s2 + arr[k], s3, s4, arr, k + 1, len) ||
                dfs(s1, s2, s3 + arr[k], s4, arr, k + 1, len) ||
                dfs(s1, s2, s3, s4 + arr[k], arr, k + 1, len));
    }
};
