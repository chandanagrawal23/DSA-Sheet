class Solution {
public:
    int solve(int day, vector<int> &travelAtDay, vector<int> &cost, vector<int> &dp)
    {
        if (day > 365)
            return 0;

        if (dp[day] != -1)
            return dp[day];  // already computed

        if (travelAtDay[day] == 0)
            return dp[day] = solve(day + 1, travelAtDay, cost, dp);  // no travel on this day

        int opt1 = cost[0] + solve(day + 1, travelAtDay, cost, dp);    // 1-day pass
        int opt2 = cost[1] + solve(day + 7, travelAtDay, cost, dp);    // 7-day pass
        int opt3 = cost[2] + solve(day + 30, travelAtDay, cost, dp);   // 30-day pass

        return dp[day] = min({opt1, opt2, opt3});
    }

    int mincostTickets(vector<int> &days, vector<int> &cost)
    {
        vector<int> travelAtDay(366, 0);  // travelAtDay[i] = 1 if traveling on day i
        for (int d : days)
            travelAtDay[d] = 1;

        vector<int> dp(366, -1);         // dp[i] = min cost to travel from day i to end

        return solve(1, travelAtDay, cost, dp);
    }
};

/*
Approach:
- Use a boolean-style array `travelAtDay[366]` to mark which days require travel.
- For each day:
   → If no travel, skip to the next day.
   → Else try buying 1-day, 7-day, or 30-day pass.
   → Recur for the next valid day accordingly.
- Use top-down DP with memoization to store already computed results.

Time Complexity: O(365)
Space Complexity: O(366) for dp + travelAtDay
*/
