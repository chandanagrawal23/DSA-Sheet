class Solution
{
public:
    bool carPooling(vector<vector<int>> &trips, int capacity)
    {
        vector<int> passengers(1001, 0); // max location is 1000

        for (auto &trip : trips)
        {
            int numPassengers = trip[0];
            int from = trip[1];
            int to = trip[2];

            passengers[from] += numPassengers;
            passengers[to] -= numPassengers;
        }

        int currentCapacity = 0;

        for (int i = 0; i < 1001; ++i)
        {
            currentCapacity += passengers[i]; // prefix sum at each point

            if (currentCapacity > capacity)
            {
                return false;
            }
        }

        return true;
    }
};
/*
Approach:
- Use a difference array (size 1001) to record passenger changes at each location.
- For each trip [num, from, to]:
    → passengers[from] += num
    → passengers[to] -= num
- Compute prefix sum to get current passengers at every location.
- If at any point capacity is exceeded, return false.

Time: O(N + 1000), Space: O(1)
*/
