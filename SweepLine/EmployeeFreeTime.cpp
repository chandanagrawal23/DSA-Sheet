// Line Sweep with MAP - NLogN , but read the other two approaches too

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> employeeFreeTime(vector<vector<int>> &schedule)
    {
        map<int, int> timeline; // time → change in number of active workers

        // Step 1: Apply difference array logic on working intervals
        for (auto &interval : schedule)
        {
            int start = interval[0];
            int end = interval[1];

            timeline[start] += 1; // worker becomes active
            timeline[end] -= 1;   // worker becomes inactive (we use 'end' not 'end + 1' because interval is [start, end))
        }

        vector<vector<int>> freeTimes;
        int active = 0;
        int lastFreeStart = -1;

        // Step 2: Traverse the timeline in sorted order
        for (auto &[time, delta] : timeline)
        {
            active += delta;

            if (active == 0)
            {
                // All workers are inactive: free interval starts
                lastFreeStart = time;
            }
            else if (lastFreeStart != -1 && time > lastFreeStart)
            {
                // Work resumes: free interval ends
                freeTimes.push_back({lastFreeStart, time});
                lastFreeStart = -1; // reset for next possible free interval
            }
        }

        return freeTimes;
    }
};

int main()
{
    Solution sol;

    // Example 1: Input format is already flattened
    vector<vector<int>> schedule = {
        {1, 3}, {6, 7}, {2, 4}, {2, 5}, {9, 12}};

    vector<vector<int>> freeTime = sol.employeeFreeTime(schedule);

    cout << "Common free time intervals:\n";
    for (auto &interval : freeTime)
    {
        cout << "[" << interval[0] << ", " << interval[1] << ")"<<"\n";
    }

    return 0;
}

/**
 Explanation:

We are given employee schedules with working intervals [start, end), and our goal is to find time ranges when no one is working.

 Steps:

 We use a difference array approach via a sorted map (sweep line):
    - At time `start`, one more person starts working → `+1`
    - At time `end`, that person stops working → `-1`
        -- We do NOT use `end + 1` because the problem clearly defines the interval as **half-open**: [start, end). 
           That means the person is **not working at time = end**, so we decrement at `end` itself.

 We simulate a sweep line over time:
    - Keep a count `active` of how many people are currently working.
    - When `active == 0`, no one is working → this is a potential start of a free time.
    - As soon as someone starts working again, we end the free time interval.

 This gives us a list of all common free times.

 Time Complexity: O(N log N)
- Sorting the time points via map traversal.

 Space Complexity: O(N)
- For the map and output result.


**/



// Approach 2 : Sabko add kro, sort kro, merge kro , and jo bhi free time hai lelo

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {

        vector<Interval> all;

        // Put everyone's working intervals together
        for (auto &employee : schedule) 
        {
            for (auto &interval : employee) 
            {
                all.push_back(interval);
            }
        }

        // Sort by start time
        sort(all.begin(), all.end(),
             [](const Interval& a, const Interval& b) {
                 return a.start < b.start;
             });

        vector<Interval> ans;

        // Merge intervals
        int start = all[0].start;
        int end = all[0].end;

        for (int i = 1; i < all.size(); i++) 
        {

            // Overlapping
            if (all[i].start <= end) 
            {
                end = max(end, all[i].end);
            }
            else 
            {
                // Gap found
                ans.push_back(Interval(end, all[i].start));

                start = all[i].start;
                end = all[i].end;
            }
        }

        return ans;
    }
};

//O(NlogN) - N is total Number of interval



--------------------------------------------------------------


// Below is NlogK 

//N = total number of intervals across all employees
 //K = number of employees

// As every list is itself sorted we can use merge K sorted List Appriach
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) 
    {

        // {start time, employee index, interval index}
        using T = tuple<int, int, int>;

        priority_queue<T, vector<T>, greater<T>> pq;

        int K = schedule.size();

        // Put first interval of every employee into heap
        for (int i = 0; i < K; i++) 
        {
            pq.push({schedule[i][0].start, i, 0});
        }

        vector<Interval> ans;
        int currentEnd = -1;

        while (!pq.empty()) 
        {

            auto [start, employee, index] = pq.top();
            pq.pop();

            Interval cur = schedule[employee][index];

            // First interval
            if (currentEnd == -1) 
            {
                currentEnd = cur.end;
            }

            // Overlap -> merge
            else if (cur.start <= currentEnd) 
            {
                currentEnd = max(currentEnd, cur.end);
            }

            // Gap -> common free time
            else 
            {
                ans.push_back(Interval(currentEnd, cur.start));
                currentEnd = cur.end;
            }

            // Push next interval of same employee
            if (index + 1 < schedule[employee].size()) 
            {
                pq.push({schedule[employee][index + 1].start, employee, index + 1});
            }
        }

        return ans;
    }
};

// K logN , K is total jobs, and N is number of intervals
