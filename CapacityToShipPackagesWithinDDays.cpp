class Solution {
public:
    // Helper function to calculate the number of days needed
    // to ship all weights with the given capacity
    int getMinDayswithGivenCapacity(vector<int>& weights , int capacity) {
        int needDays = 1;
        int cur = 0;
        int n = weights.size();
        int i = 0;
        while(i < n) {
            if(cur + weights[i] > capacity) {
                cur = 0;
                needDays++;
            } else {
                cur += weights[i++];
            }
        }
        return needDays;
    }

    int shipWithinDays(vector<int>& weights, int D) {
        int left = 0, right = 25000000;
        int answer = -1;

        // Set left to max of all weights as minimum capacity
        for (int w : weights)
            left = max(left, w);

        // Binary search with left <= right
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            // Check how many days are needed with this mid capacity
            if(getMinDayswithGivenCapacity(weights , mid) <= D)
            {
                answer = mid;       // Valid capacity, store result
                right = mid - 1;    // Try to find smaller valid capacity
            }
            else
            {
                left = mid + 1;     // Too small, need to increase
            }
        }
        return answer;
    }
};
