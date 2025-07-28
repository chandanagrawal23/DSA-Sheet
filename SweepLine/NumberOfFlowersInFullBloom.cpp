// Sweep Line WOWWWWW...........
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &peopleArrivalTime)
    {
        map<int, int> diff;

        // Step 1: Mark start and end+1 of each flower using difference array logic
        for (auto &f : flowers)
        {
            diff[f[0]] += 1;       // flower starts blooming
            diff[f[1] + 1] -= 1;   // flower ends blooming after f[1]
        }

        // Step 2: Traverse the diff map (auto-sorted by time)
        // and build prefix sum to count how many flowers are blooming at each unique time
        vector<int> bloomTime;   // stores time points where change occurs
        vector<int> bloomCount;  // number of flowers blooming at corresponding time

        int current = 0;
        for (auto &[time, delta] : diff)
        {
            current += delta;  // add/subtract flower count change
            bloomTime.push_back(time);
            bloomCount.push_back(current);
        }

        /*
        Example:
        flowers = [[1,5],[2,7],[4,6]]
        diff = {1:+1, 2:+1, 4:+1, 6:-1, 7:-1, 8:-1}

        After prefix sum:
        bloomTime:   [1, 2, 4, 6, 7, 8]
        bloomCount:  [1, 2, 3, 2, 1, 0]

        Means:
        - at time 1 → 1 flower
        - at time 2 → 2 flowers
        - at time 4 → 3 flowers  , iska matlb hai ki time 2 to time 3 tak 2 flowers , but at time 4 flower is 3
        - at time 6 → 2 flowers  , iska matlb hai ki time 4 to time 5 tak 3 flowers , but at time 6 flower is 2
        - at time 7 → 1 flower
        - at time 8 → 0 flowers
        */

        // Step 3: For each person, find how many flowers were blooming at their arrival time
        vector<int> result;
        for (int pTime : peopleArrivalTime)
        {
            /*
            We want to find the latest bloomTime which is <= pTime
            So we use upper_bound, which returns:
            - index of first time strictly > pTime
            - then we do (idx - 1) to get last time <= pTime
            */

            int idx = upper_bound(bloomTime.begin(), bloomTime.end(), pTime) - bloomTime.begin();

            if (idx == 0)
            {
                // All bloom times are after pTime → no flower was blooming yet
                result.push_back(0);
            }
            else
            {
                // bloomTime[idx - 1] is the last time ≤ pTime
                result.push_back(bloomCount[idx - 1]);
            }
        }

        return result;
    }
};

/*
 Explanation:

- diff[t]: stores +1 when a flower starts at t, and -1 at t+1 when it ends
- map is used instead of array because time can go up to 1e9
- Prefix sum over sorted keys in map gives number of active flowers at each time

 For each person:
- We use upper_bound on bloomTime to find the first time > personArrival
- Then bloomCount[idx - 1] gives count of flowers blooming at that time

 Time Complexity: O(N log N + Q log N)
   - N = number of flowers, Q = number of people
   - log N per person due to binary search

 Space: O(N) for prefix arrays bloomTime and bloomCount
*/
