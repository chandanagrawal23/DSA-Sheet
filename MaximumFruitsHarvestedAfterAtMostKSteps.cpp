// Brute Force Approach - O(N^2)
// Try all possible subarrays and check if they can be covered within K steps   
// NOTE : For AC , please use other optimised approach DYNAMIC SLIDING WINDOW
class Solution
{
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k)
    {
        int n = fruits.size();
        int maxFruits = 0;

        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            for (int j = i; j < n; ++j)
            {
                int left = fruits[i][0];
                int right = fruits[j][0];

                // Minimum steps needed to cover range [left...right] starting from startPos
                /*
                You want to know: can I start at startPos and visit all fruit positions
                 between fruits[i][0] and fruits[j][0] within K steps?

                The shortest way to cover a segment [left, right] from startPos is:
                */
                int steps = min(abs(startPos - left), abs(startPos - right)) + (right - left);

                if (steps > k)
                    break;

                sum += fruits[j][1];
                maxFruits = max(maxFruits, sum);
            }
        }

        return maxFruits;
    }
};

/*
Approach Explanation:

- Problem:
    Given a list of fruit positions and their quantities, and a starting point, we want to collect
    maximum fruits by visiting a contiguous segment within at most K steps.

- Brute-force idea:
    1. For each pair (i, j) of fruit positions, check if we can collect fruits in range [i..j].
    2. Compute the minimum steps to cover both ends starting from startPos:
           steps = min(|start - left|, |start - right|) + (right - left)
    3. If steps <= K, accumulate fruits in that segment.
    4. Keep track of the maximum total collected.

- Why this works:
    The logic for steps ensures that we visit the entire interval [left...right] optimally —
    starting from the nearer end and sweeping to the farther one.

- Time Complexity: O(N^2)
    Because we are considering all pairs (i, j) in nested loops.

- Space Complexity: O(1)
    No extra space used apart from a few variables.
*/


//====================================================================================================================================================
class Solution
{
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k)
    {
        int n = fruits.size();
        int left = 0, right = 0, sum = 0, ans = 0;

        // Sort fruits by position (guaranteed sorted in problem)
        while (right < n)
        {
            sum += fruits[right][1];

            // While range is too far from startPos
            while (left <= right && !canVisit(fruits[left][0], fruits[right][0], startPos, k))
            {
                sum -= fruits[left][1];
                left++;
            }

            ans = max(ans, sum);
            right++;
        }

        return ans;
    }

    /* 
    Minimum steps needed to cover range [left...right] starting from startPos
    You want to know: can I start at startPos and visit all fruit positions
        between fruits[i][0] and fruits[j][0] within K steps?

    The shortest way to cover a segment [left, right] from startPos is:
            left < startPos < right 
    min(abs(start - l), abs(start - r)) + (r - l);
    */
    bool canVisit(int l, int r, int start, int k)
    {
        // Try going to the left end or right end first, then across
        int steps = min(abs(start - l), abs(start - r)) + (r - l);
        return steps <= k;
    }
};  

/*
Approach:
-----------
- Use sliding window on the sorted fruit positions.
- Keep a window [left...right] where all positions are visitable within k steps.
- For each valid window, calculate total fruits collected.
- To check if a window is valid:
    min(abs(start - left), abs(start - right)) + (right - left) <= k
- Update max fruits collected during traversal.

Time: O(n), Space: O(1)
*/




