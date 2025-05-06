class Solution {
public:
    // Helper function to check if we can distribute items such that
    // no store gets more than maxItemsPerStore
    bool canDistribute(const vector<int>& quantities, int numStores, int maxItemsPerStore) {
        int storesNeeded = 0;
        for (int quantity : quantities) {
            storesNeeded += quantity / maxItemsPerStore;
            if (quantity % maxItemsPerStore != 0)
                storesNeeded++;  // Add 1 if remainder exists
        }
        return storesNeeded <= numStores;
    }

    int minimizedMaximum(int numStores, vector<int>& quantities) {
        int low = 1;
        int high = *max_element(quantities.begin(), quantities.end());
        int answer = high;  // Worst case, max element as initial answer

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canDistribute(quantities, numStores, mid)) {
                answer = mid;       // Valid distribution, try smaller value
                high = mid - 1;
            } else {
                low = mid + 1;      // Need to allow more per store
            }
        }

        return answer;
    }
};
