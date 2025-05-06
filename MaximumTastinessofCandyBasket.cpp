class Solution {
public:
    // Main function to find the maximum tastiness possible
    int maximumTastiness(vector<int>& price, int k) 
    {
        // Sort the prices to allow optimal selection of items
        sort(price.begin(), price.end());

        int lo = 0, hi = price.back() - price.front();  // Range for binary search
        int ans = -1;  // Variable to store the result

        // Binary search for maximum tastiness
        while (lo <= hi) 
        {
            int mid = lo + (hi - lo) / 2;  // Calculate mid point

            // Check if it's possible to select 'k' items with at least 'mid' tastiness
            if (check(mid, price, k)) 
            {
                ans = mid;  // Update answer with 'mid'
                lo = mid + 1;  // Try for a larger tastiness
            }
            else
            {
                hi = mid - 1;  // Try a smaller tastiness
            }
        }

        return ans;  // Return the maximum tastiness
    }

    // Helper function to check if it's possible to select 'k' items with at least 'x' tastiness
    bool check(int x, vector<int>& price, int k)
    {
        int lastSelectedPrice = price[0];  // Price of the last selected item
        int selectedCount = 1;  // Count of selected items
        int i = 1;  // Iterator for the price array

        // Try to select 'k' items with a minimum difference of 'x' tastiness
        while (selectedCount < k && i < price.size())
        {
            if (price[i] - lastSelectedPrice >= x)  // If the price difference is enough
            {
                lastSelectedPrice = price[i];  // Update the last selected item's price
                selectedCount++;  // Increment selected items count
            }
            i++;  // Move to the next item
        }

        return (selectedCount == k);  // Return true if exactly 'k' items were selected
    }
};
