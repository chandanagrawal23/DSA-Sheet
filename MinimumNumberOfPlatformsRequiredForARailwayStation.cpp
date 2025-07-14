#include <bits/stdc++.h>
using namespace std;

// Learn Approach 2 3 4 for interview

/////////////////////////////////////////////////////
// 1. Brute Force Approach (DO NOT WRITE IN INTERVIEW)
/////////////////////////////////////////////////////
class SolutionBruteForce
{
public:
    pair<int, int> getMinPlatforms(vector<vector<int>> &intervals)
    {
        int minTime = INT_MAX, maxTime = INT_MIN;

        // Find the min and max time in the intervals
        for (auto &v : intervals)
        {
            minTime = min(minTime, v[0]);
            maxTime = max(maxTime, v[1]);
        }

        int maxPlatforms = 0, timeOfMax = -1;

        // For each time unit, count how many trains are at the station
        for (int t = minTime; t <= maxTime; t++)
        {
            int count = 0;
            for (auto &v : intervals)
            {
                if (v[0] <= t && t < v[1]) // active interval
                    count++;
            }
            if (count > maxPlatforms)
            {
                maxPlatforms = count;
                timeOfMax = t;
            }
        }

        return {maxPlatforms, timeOfMax};
    }
};

/*
Approach:
Check every time unit from the earliest start to the latest end.
Count how many trains are present at each time.
Track the time with the maximum count.
Time complexity: O(N * T), where T is the time range.
*/

/////////////////////////////////////////////////////
// 2. Two Pointers Approach
/////////////////////////////////////////////////////
class SolutionTwoPointers
{
public:
    pair<int, int> getMinPlatforms(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        vector<int> start, end;

        // Split start and end times
        for (auto &v : intervals)
        {
            start.push_back(v[0]);
            end.push_back(v[1]);
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i = 0, j = 0, current = 0, maxPlatforms = 0, timeOfMax = -1;

        // Simulate timeline with two pointers
        while (i < n && j < n)
        {
            if (start[i] < end[j])
            {
                current++; // train arrives
                if (current > maxPlatforms)
                {
                    maxPlatforms = current;
                    timeOfMax = start[i];
                }
                i++;
            }
            else
            {
                current--; // train departs
                j++;
            }
        }

        return {maxPlatforms, timeOfMax};
    }
};

/*
Approach:
Sort all start and end times.
Use two pointers to traverse the timeline.
Increment platform count on arrival, decrement on departure.
Track maximum platform usage and the corresponding time.
Time complexity: O(N log N)
*/

/////////////////////////////////////////////////////
// 3. Line Sweep Approach
/////////////////////////////////////////////////////
class SolutionLineSweep
{
public:
    pair<int, int> getMinPlatforms(vector<vector<int>> &intervals)
    {
        vector<pair<int, int>> events;

        // Convert to events: +1 for arrival, -1 for departure
        for (auto &v : intervals)
        {
            events.push_back({v[0], +1});
            events.push_back({v[1], -1});
        }

        // Sort events: if same time, arrivals (+1) come before departures (-1)
        sort(events.begin(), events.end(), [](auto &a, auto &b) {
            if (a.first == b.first)
                return a.second > b.second;
            return a.first < b.first;
        });

        int current = 0, maxPlatform = 0, timeOfMax = -1;

        // Sweep line over time
        for (auto &[time, type] : events)
        {
            current += type;
            if (current > maxPlatform)
            {
                maxPlatform = current;
                timeOfMax = time;
            }
        }

        return {maxPlatform, timeOfMax};
    }
};

/*
Approach:
Create +1 and -1 events for arrival and departure.
Sort all events by time. On same time, prioritize arrival.
Do a prefix sum over events to simulate current platform usage.
Track the max usage and its time.
Time complexity: O(N log N)
*/

/////////////////////////////////////////////////////
// 4. Min Heap (Greedy)
/////////////////////////////////////////////////////
class SolutionMinHeap
{
public:
    pair<int, int> getMinPlatforms(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end()); // sort by arrival time
        priority_queue<int, vector<int>, greater<int>> minHeap;

        int maxPlatforms = 0;
        int timeOfMax = -1;

        for (auto &v : intervals)
        {
            int start = v[0], end = v[1];

            // Free platforms that are done before current train starts
            while (!minHeap.empty() && minHeap.top() <= start)
            {
                minHeap.pop();
            }

            minHeap.push(end); // assign platform

            // Track max usage and time
            if ((int)minHeap.size() > maxPlatforms)
            {
                maxPlatforms = minHeap.size();
                timeOfMax = start;
            }
        }

        return {maxPlatforms, timeOfMax};
    }
};

/*
Approach:
Sort intervals by start time.
Use a min heap to track the earliest end time of occupied platforms.
Pop from heap when a platform is freed (train departs).
Push end time of current train into the heap.
The heap size at any point = number of platforms in use.
Track max size and corresponding time.
Time complexity: O(N log N)
*/

/////////////////////////////////////////////////////
// Main Function to Run All Approaches
/////////////////////////////////////////////////////
int main()
{
    vector<vector<int>> intervals = {
        {900, 910},
        {940, 1200},
        {950, 1120},
        {1100, 1130},
        {1500, 1900},
        {1800, 2000}};

    SolutionBruteForce s1;
    auto [p1, t1] = s1.getMinPlatforms(intervals);
    cout << "[BruteForce] Max platforms: " << p1 << " at time: " << t1 << "\n";

    SolutionTwoPointers s2;
    auto [p2, t2] = s2.getMinPlatforms(intervals);
    cout << "[TwoPointers] Max platforms: " << p2 << " at time: " << t2 << "\n";

    SolutionLineSweep s3;
    auto [p3, t3] = s3.getMinPlatforms(intervals);
    cout << "[LineSweep] Max platforms: " << p3 << " at time: " << t3 << "\n";

    SolutionMinHeap s4;
    auto [p4, t4] = s4.getMinPlatforms(intervals);
    cout << "[MinHeap] Max platforms: " << p4 << " at time: " << t4 << "\n";

    return 0;
}

/*
Approach:
Test all four methods on a sample dataset.
Each prints max platform count and the corresponding time.
*/
