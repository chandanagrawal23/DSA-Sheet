class Solution {
public:
    // Helper function to calculate how many trips can be completed in 'givenTime'
    long long int countTrips(vector<int>& timePerTrip, long long int givenTime) {
        long long int totalTrips = 0;
        for (auto t : timePerTrip) {
            totalTrips += (givenTime / t);  // Each worker can do (givenTime / time[i]) trips
        }
        return totalTrips;
    }

    // Binary search to find the minimum time required to complete 'totalTrips'
    long long minimumTime(vector<int>& timePerTrip, int totalTrips) {
        long long int low = 1;
        long long int high = 1e14;  // Upper bound based on constraints
        long long int result = low;

        while (low <= high) {
            long long int mid = low + (high - low) / 2;
            long long int tripsDone = countTrips(timePerTrip, mid);

            if (tripsDone >= totalTrips) {
                result = mid;       // Try to minimize further
                high = mid - 1;
            } else {
                low = mid + 1;      // Need more time
            }
        }
        return result;
    }
};
