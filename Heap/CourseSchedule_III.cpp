class Solution
{
public:
    static bool cmp(vector<int> &a, vector<int> &b)
    {
        return a[1] < b[1]; // Sort by course deadline (lastDay)
    }

    int scheduleCourse(vector<vector<int>> &courses)
    {
        sort(courses.begin(), courses.end(), cmp); // Sort by deadline

        priority_queue<int> maxHeap; // Max heap to store course durations
        int totalTime = 0;

        for (auto &course : courses)
        {
            int duration = course[0];
            int deadline = course[1];

            if (totalTime + duration <= deadline)
            {
                // If we can take this course within time, take it
                totalTime += duration;
                maxHeap.push(duration);
            }
            else if (!maxHeap.empty() && maxHeap.top() > duration)
            {
                // Replace longest course with current if it's shorter
                totalTime += duration - maxHeap.top();
                maxHeap.pop();
                maxHeap.push(duration);
            }
        }

        return maxHeap.size(); // Total courses taken
    }
};

/*

Approach:
==========
- Sort all courses by their deadline (lastDay).
- Use a max heap to track durations of courses we've taken.
- Iterate over each course:
   - If it fits within current time, take it and add its duration.
   - If not, and it's shorter than the longest course taken so far → replace it.
- Greedy logic: Always keep total time low by keeping shortest durations possible.

Time: O(n log n) for sorting + O(n log n) for heap operations
Space: O(n) for heap

*/
