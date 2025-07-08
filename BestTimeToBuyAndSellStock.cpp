class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        int minPriceSoFar = INT_MAX;  // Lowest price seen so far
        int maxProfitSoFar = 0;       // Max profit found so far

        for (int price : prices)
        {
            minPriceSoFar = min(minPriceSoFar, price);               // Update min price if current is lower
            maxProfitSoFar = max(maxProfitSoFar, price - minPriceSoFar); // Max profit if sold today
        }

        return maxProfitSoFar;
    }
};

/*
Approach:
- Track the lowest price so far (minPriceSoFar)
- For each day, calculate potential profit if sold today
- Update max profit if the current potential profit is higher

Time Complexity: O(n)   // One pass through prices
Space Complexity: O(1)  // Constant space
*/
