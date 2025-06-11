class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) 
   {
        if (intervals.empty()) 
        {
            return true;
        }

        // Note: C++ sort function automatically sorts a vector first, by the 1st element( start of interval), then by the 2nd element(ending of interval) and so on.
        sort(intervals.begin(), intervals.end());

        for (int i = 0; i < intervals.size() - 1; i++) 
        {
            // if ending of first interval is after the starting of next interval means overalp
            if (intervals[i][1] > intervals[i + 1][0]) {
                return false;
            }
        }
        return true;
    }
};
