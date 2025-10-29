class Solution
{
private:
    int N;
    vector<int> memo; // dynamic memoization vector

    int dfs(vector<vector<int>> &nums, int idx)
    {
        if (idx >= N)
            return 0; // base case: no more jobs

        if (memo[idx] != -1)
            return memo[idx]; // return already computed value

        int lo = 0, hi = N - 1, newJobTime = N + 1;

        // binary search to find next non-overlapping job
        while (lo <= hi)
        {
            int mid = (lo + hi) >> 1;
            if (nums[mid][0] >= nums[idx][1])
            {
                newJobTime = mid;
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }

        // take max of skipping or taking next non overlapping job
        return memo[idx] = max(
            dfs(nums, idx + 1),
            nums[idx][2] + dfs(nums, newJobTime)
        );
    }

public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        N = size(profit);
        vector<vector<int>> nums;

        // combine start, end, and profit
        for (int i = 0; i < N; ++i)
            nums.push_back({startTime[i], endTime[i], profit[i]});

        // sort by start time
        sort(begin(nums), end(nums));

        // initialize memo with -1 for uncomputed states
        memo.assign(N, -1);

        // compute max profit using dfs + memoization
        return dfs(nums, 0);
    }
};

/*
APPROACH:

We are solving the "Weighted Job Scheduling" problem using recursion + memoization + binary search.

1. Sort jobs by their start time.
2. For each job at index `idx`, we have two choices:
   → Skip this job: move to idx + 1
   → Take this job: add its profit + recursively take the next non-overlapping job.
3. To find the next job that starts after current job ends,
   we perform a binary search on start times (O(log N)).
4. Memoize results in a dynamic vector to avoid recomputation.

TIME COMPLEXITY:
- Sorting: O(N log N)
- DFS recursion with memoization: O(N)
- Each DFS step does binary search: O(log N)
→ Total = O(N log N)

SPACE COMPLEXITY:
- O(N) for recursion + memo vector

*/
