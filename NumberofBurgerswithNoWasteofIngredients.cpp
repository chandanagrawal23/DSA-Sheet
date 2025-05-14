class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) 
    {
        // Total number of burgers is equal to cheese slices
        int totalBurgers = cheeseSlices;
        
        // Set binary search bounds for number of jumbo burgers
        int minBurger = 0;
        int maxBurger = totalBurgers;
    
        while(minBurger <= maxBurger)
        {
            // Try mid value as a possible number of jumbo burgers
            int jumbo = minBurger + (maxBurger - minBurger)/2;

            // Remaining burgers are small burgers
            int small = totalBurgers - jumbo;

            // Calculate total tomato slices needed for this combination
            int calculatedTomatoSlices = 4*jumbo + 2*small;

            // If the combination matches the given tomato slices, return it
            if(tomatoSlices == calculatedTomatoSlices)
            {
                return {jumbo , small};
            }

            // If too many tomato slices are used, reduce jumbo burgers
            if(calculatedTomatoSlices > tomatoSlices)
            {
                maxBurger = jumbo - 1;
            }
            // If too few tomato slices, increase jumbo burgers
            else
            {
                minBurger = jumbo + 1;
            }
        }

        // Return empty if no valid combination found
        return {};
    }
};
