class Solution
{
public:
    int mostBooked(int n, vector<vector<int>>& meetings)
    {
        sort(meetings.begin(), meetings.end());

        priority_queue<int, vector<int>, greater<int>> available;
        
        // roomIdx
        for (int i = 0; i < n; i++)
        {
            available.push(i);
        }
        // {endTime, roomIdx}
        priority_queue<pair<long long, int>,vector<pair<long long, int>>,greater<pair<long long, int>>> busy;

        vector<int> cnt(n, 0);

        for (auto& meeting : meetings)
        {
            long long start = meeting[0];
            long long end = meeting[1];

            long long duration = end - start;

            while (!busy.empty() && busy.top().first <= start)
            {
                available.push(busy.top().second);
                busy.pop();
            }

            if (!available.empty())
            {
                int room = available.top();
                available.pop();

                busy.push({end, room});
                cnt[room]++;
            }
            else
            {
                auto [freeTime, room] = busy.top();
                busy.pop();

                busy.push({freeTime + duration, room});
                cnt[room]++;
            }
        }

        int ans = 0;

        for (int i = 1; i < n; i++)
        {
            if (cnt[i] > cnt[ans])
            {
                ans = i;
            }
        }

        return ans;
    }
};

/*

Approach: Two Min Heaps (Greedy)
1. Sort meetings: Sort all meetings by their start time so that we process meetings in chronological order.

2. Available Rooms Min Heap: Maintain a min heap containing available room indices. The smallest room index gets the highest priority.

3. Busy Rooms Min Heap: Maintain another min heap storing {endTime, roomIdx}.
- First priority: Earliest ending time.
- If ending times are equal, smaller room index gets priority.
4. Process each meeting:
- Calculate the meeting duration (end - start).
- Free all rooms whose meeting end time is less than or equal to the current meeting's start time. Push their room indices into the available heap.
- If an available room exists:
  - Assign the smallest indexed room.
  - Push {end, roomIdx} into the busy heap.
- If no room is available:
  - Pick the room that becomes free earliest.
  - If multiple rooms have the same end time, the smaller indexed room is selected automatically.
  - Delay the meeting until that room becomes free.
  - Its new end time becomes freeTime + duration.
- Increment the meeting count for the assigned room.
5. Find the answer: Traverse the frequency array and return the room index that hosted the maximum number of meetings. If frequencies are equal, return the smallest room index.
Complexity Analysis
- Sorting meetings: (O(mlog m))
- Initializing available rooms: (O(nlog n))
- Processing meetings: (O(mlog n))
  - Each meeting is pushed into and popped from the heaps at most once.
- Finding the maximum frequency: (O(n))
Time Complexity: (O(mlog m + (m+n)log n))

Space Complexity: (O(n+m)) including the input sorting space in the general case; auxiliary heap and frequency space is (O(n)).

Where:
- (n) = Number of rooms.
- (m) = Number of meetings.

*/
