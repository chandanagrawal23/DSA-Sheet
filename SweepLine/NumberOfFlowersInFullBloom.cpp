// Sweep Line WOWWWWW...........
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &peopleArrivalTime)
    {
        map<int, int> diff;

        // Mark start and end+1 of bloom using map
        for (auto &f : flowers)
        {
            diff[f[0]] += 1;
            diff[f[1] + 1] -= 1;
        }

        // Traverse in order and compute prefix sum
        vector<int> bloomTime;
        vector<int> bloomCount;

        int current = 0;
        for (auto &[time, delta] : diff)
        {
            current += delta;
            bloomTime.push_back(time);
            bloomCount.push_back(current);
        }

        // For each person, find the last bloomTime <= personArrivalTime using upper_bound
        vector<int> result;
        for (int pTime : peopleArrivalTime)
        {
            int idx = upper_bound(bloomTime.begin(), bloomTime.end(), pTime) - bloomTime.begin();
            if (idx == 0)
                result.push_back(0); // no flower yet
            else
                result.push_back(bloomCount[idx - 1]);
        }

        return result;
    }
};

/*
 Explanation:

- diff[t] stores +1 at flower start and -1 at flower end + 1
- Since time values are large (up to 1e9), we use map instead of array.
- prefix sum over sorted keys gives active flower count at each unique time.
- For each person:
   - use upper_bound to find how many flowers were blooming <= their time

 Time: O(N log N + Q log N)
   - N = flowers.size(), Q = people.size()
   - log N for each query due to upper_bound

 Space: O(N) for prefix arrays
*/





//////////////////////////////////////////////////////////////////////////////////////////
/*
If the constraints are not that much big, then we simply did

Difference Array  + Prefix Sum liek Below-

*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people)
    {
        const int MAX_TIME = 1e5 + 2;
        vector<int> diff(MAX_TIME, 0);

        // Mark difference array
        for (auto &f : flowers)
        {
            diff[f[0]] += 1;
            if (f[1] + 1 < MAX_TIME)
                diff[f[1] + 1] -= 1;
        }

        // Compute prefix sum: bloomCount[t] = #flowers in bloom at time t
        vector<int> bloomCount(MAX_TIME, 0);
        bloomCount[0] = diff[0];
        for (int i = 1; i < MAX_TIME; i++)
        {
            bloomCount[i] = bloomCount[i - 1] + diff[i];
        }

        // Answer each person's query in O(1)
        vector<int> result;
        for (int t : people)
        {
            result.push_back(bloomCount[t]);
        }

        return result;
    }
};

/*
 Approach:

1. Use a difference array `diff[]` to track when flowers bloom and fade.
2. Compute prefix sum → gives how many flowers are blooming at each time.
3. Query for each person in O(1).

 Time: O(N + MAX_TIME + Q)
 Space: O(MAX_TIME)
  Where N = #flowers, Q = #people

 Only feasible when time bounds are small, like ≤ 1e5.
*/
