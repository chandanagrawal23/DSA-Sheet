class Solution
{
public:
    // Check if current radius can heat all houses
    bool canAllHousesBeHeated(vector<int> &heaters, vector<int> &houses, int radius)
    {
        int houseIdx = 0;
        for (int heater : heaters)
        {
            while (houseIdx < houses.size() &&
                   houses[houseIdx] >= heater - radius &&
                   houses[houseIdx] <= heater + radius)
            {
                houseIdx++;
            }

            // early exit
            if(houseIdx == houses.size())
                return true;
        }
        return houseIdx == houses.size(); // All houses covered
    }

    int findRadius(vector<int> &houses, vector<int> &heaters)
    {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        int left = 0, right = 1e9;
        int answer = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (canAllHousesBeHeated(heaters, houses, mid))
            {
                answer = mid;      // Mid works, try smaller radius
                right = mid - 1;
            }
            else
            {
                left = mid + 1;    // Mid too small, increase radius
            }
        }

        return answer;
    }
};

/*

Approach:
- Each heater can heat houses in the range [heater - radius, heater + radius]
- Binary search on the minimum required radius in range [0, 1e9]
- For each mid (radius), check if all houses are covered using a two-pointer scan
- If mid works → store as possible answer and search left
- If not → increase radius

Time: O((H + N) log(1e9)), where H = #houses, N = #heaters
Space: O(1)

*/
