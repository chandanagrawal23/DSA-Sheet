class Solution
{
public:
    // Helper: Calculate total available power if each battery can contribute up to `maxTime`
    long long getTotalAvailablePower(const vector<int>& batteries, long long maxTime)
    {
        long long total = 0;
        for (int charge : batteries)
        {
            total += min((long long)charge, maxTime);
        }
        return total;
    }

    long long maxRunTime(int computers, vector<int>& batteries)
    {
        long long left = 0;
        long long right = accumulate(batteries.begin(), batteries.end(), 0LL) / computers;
        long long answer = 0;

        while (left <= right)
        {
            long long midTime = left + (right - left) / 2;
            long long totalAvailable = getTotalAvailablePower(batteries, midTime);

            if (totalAvailable >= computers * midTime)
            {
                answer = midTime;      // valid runtime, try more
                left = midTime + 1;
            }
            else
            {
                right = midTime - 1;   // not enough, try less
            }
        }

        return answer;
    }
};

/*

Approach:
- We want to run `computers` machines simultaneously for as long as possible.
- Each battery can be used fully or up to a limit of `midTime`.
- We binary search for the maximum possible `midTime`.

Steps:
1. Binary search over time range [0, totalPower / computers].
2. For each candidate time `midTime`, calculate total usable power using:
      min(battery, midTime) for each battery.
3. If total power ≥ computers * midTime → feasible → try longer.
4. Else → not feasible → try shorter.

Why it works:
- The feasibility function is monotonic → binary search is valid.

Time: O(n * log(totalPower / computers))  
Space: O(1)

*/
