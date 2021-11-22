//https://leetcode.com/problems/meeting-rooms-ii/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
//         for(auto xt : intervals)
//             cout<<xt[0]<<" "<<xt[1]<<endl;
        priority_queue<int , vector<int> , greater<int>>pq;
        for(auto xt : intervals)
        {
            if(!pq.empty() and pq.top()<=xt[0])
                pq.pop();
            pq.push(xt[1]);
        }
        return pq.size();
    }
};


/*


Algorithm we will sort our interval according to starting point,obviously we will care the meeting which will scheduled at 9 am rather than 9 pm , 

Now after that , we will remove that meeting which ends earlier.

PSEUDO - 

Sort the given meetings by their start time.
Initialize a new min-heap and add the first meeting's ending time to the heap. We simply need to keep track of the ending times as that tells us when a meeting room will get free.
For every meeting room check if the minimum element of the heap i.e. the room at the top of the heap is free or not.
If the room is free, then we extract the topmost element and add it back with the ending time of the current meeting we are processing.
If not, then we allocate a new room and add it to the heap.
After processing all the meetings, the size of the heap will tell us the number of rooms allocated. This will be the minimum number of rooms needed to accommodate all the meetings.
*/
