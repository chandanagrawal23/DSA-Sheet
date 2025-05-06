class Solution {
public:
    // Check if it's possible to give at least 'k' kids 'size' candies each
    bool isFeasible(int size, const vector<int>& candies, long long kids) {
        if (size == 0) return true; // Can't divide by 0

        long long totalKids = 0;

        for (int pile : candies) {
            totalKids += pile / size;
            if (totalKids >= kids) return true; // Early exit if possible
        }

        return false;
    }

    int maximumCandies(vector<int>& candies, long long k) {
        long long low = 1;
        long long high = *max_element(candies.begin(), candies.end());
        long long answer = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (isFeasible(mid, candies, k)) {
                answer = mid;       // Valid size found, try for a bigger one
                low = mid + 1;
            } else {
                high = mid - 1;     // Too large size, try smaller
            }
        }

        return (int)answer;
    }
};
