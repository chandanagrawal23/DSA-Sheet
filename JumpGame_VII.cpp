class Solution
{
public:
    bool canReach(string s, int minJump, int maxJump)
    {
        int n = s.length();

        if (s[n - 1] != '0')
        {
            return false; // If destination is not '0', cannot reach
        }

        queue<int> q;
        q.push(0); // Start from index 0

        int farthest = 0; // Tracks the farthest index we've already considered from previous jumps

        while (!q.empty())
        {
            int index = q.front();
            q.pop();

            // If we reach the last index, return true
            if (index == n - 1)
            {
                return true;
            }

            // Explore all valid jump targets from current index
            for (int j = max(index + minJump, farthest); j <= min(index + maxJump, n - 1); ++j)
            {
                if (s[j] == '0')
                {
                    q.push(j);
                }
            }

            // Update farthest to avoid revisiting already processed indices
            farthest = min(index + maxJump + 1, n);
        }

        return false;
    }
};

/*
Approach:
---------
- Use BFS to explore all reachable indices from 0.
- For each position, consider jumps in the range [i + minJump, i + maxJump].
- Only jump to positions with '0' and avoid re-processing ranges using `farthest`.
- Early exit if index n-1 is reached.

Key Optimization:
- Use a `farthest` variable to skip previously explored ranges and avoid TLE.

Time Complexity: O(n)
- Each index is pushed into the queue at most once.

Space Complexity: O(n)
- For the queue storing visited indices.
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution
{
public:
    bool canReach(string s, int minJump, int maxJump)
    {
        int n = s.size();
        int nextStart = 0;  // The farthest position already checked for spreading '2'

        for (int i = 0; i < n; ++i)
        {
            // We only spread from index 0 or previously marked reachable positions
            if (i == 0 || s[i] == '2')
            {
                // Spread reachability to the right in the jump range
                for (int j = max(i + minJump, nextStart); j <= min(i + maxJump, n - 1); ++j)
                {
                    if (s[j] == '0')
                    {
                        s[j] = '2';  // Mark as reachable
                    }
                }
                nextStart = min(i + maxJump + 1, n);  // Update the window
            }
        }

        return s[n - 1] == '2';  // Final index must be reachable
    }
};

/*
Approach:
---------
- Use greedy-like two pointer strategy.
- Treat '2' as visited or reachable characters.
- Start from index 0, and for each reachable index i, mark all unvisited '0's in range [i+minJump, i+maxJump] as '2'.
- Maintain `nextStart` to avoid revisiting already processed indices.

Key Optimizations:
- Avoids extra space like visited[] or queue.
- Each index is visited at most once, making it faster than naive BFS.

Time Complexity: O(n)
- Every index is processed once in outer loop and inner range only visits unvisited positions.

Space Complexity: O(1)
- Modifies input string in-place (no auxiliary data structures).
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Solution
{
public:
    bool canReach(string s, int minJump, int maxJump)
    {
        int n = s.length();
        vector<bool> dp(n, false);  // dp[i] = true if index i is reachable
        dp[0] = true;

        int reachableCount = 0;  // Rolling count of reachable indices in the current window

        for (int i = 1; i < n; ++i)
        {
            // Start adding reachable states once we hit minJump
            if (i >= minJump)
            {
                reachableCount += dp[i - minJump];
            }

            // Slide the window: remove leftmost if out of jump range
            if (i > maxJump)
            {
                reachableCount -= dp[i - maxJump - 1];
            }

            // We can reach index i if it's '0' and at least one dp[j] in [i-maxJump, i-minJump] is true
            dp[i] = (s[i] == '0' && reachableCount > 0);
        }

        return dp[n - 1];
    }
};

/*
Approach:
---------
- Use dynamic programming where dp[i] = true if index i is reachable.
- Instead of scanning full [i - maxJump, i - minJump] every time (which is O(n^2)),
  we maintain a sliding window sum (reachableCount) of reachable positions.
- Update reachableCount by adding dp[i - minJump] and subtracting dp[i - maxJump - 1].

Key Insight:
- This is a prefix sum optimization over the BFS-style approach.

Time Complexity: O(n)
- Each index is visited once; no nested loops.

Space Complexity: O(n)
- Extra space used for the dp array.
*/

