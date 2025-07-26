class Solution
{
public:
    int minMeetingRooms(vector<vector<int>>& intervals)
    {
        // Use a map to simulate the timeline of meetings
        // Key: time point, Value: +1 for meeting start, -1 for meeting end
        map<int, int> timeline;

        for (const auto& interval : intervals)
        {
            timeline[interval[0]]++;  // meeting starts
            timeline[interval[1]]--;  // meeting ends
        }

        int ongoingMeetings = 0;
        int maxRooms = 0;

        // Traverse the timeline in sorted order
        for (const auto& [time, countChange] : timeline)
        {
            ongoingMeetings += countChange;             // update current ongoing meetings
            maxRooms = max(maxRooms, ongoingMeetings);  // track max needed rooms
        }

        return maxRooms;
    }
};

// Approach:
// Use the sweep line algorithm to track meeting start and end events on a timeline.
// For each meeting, increment the count at start time and decrement at end time.
// Then, traverse the timeline in order and track the number of ongoing meetings.
// The peak number of concurrent meetings gives the minimum rooms needed.

// Time Complexity: O(n log n)
// - Inserting into the map takes O(log n), and we do this for 2n time points.
// - Total time: O(n log n)

// Space Complexity: O(n)
// - We store up to 2n entries in the map for all start and end times.
