class Solution 
{
public:

    // Function to count how many bouquets can be made by a given number of days
    int getNumOfBouquets(const vector<int>& bloomDay, int days, int k) 
    {
        int numOfBouquets = 0;
        int consecutiveFlowers = 0;

        for (int i = 0; i < bloomDay.size(); i++) 
        {
            if (days >= bloomDay[i]) 
            {
                consecutiveFlowers++;  // Flower blooms on time
            } 
            else
            {
                consecutiveFlowers = 0;  // Reset if not bloomed yet
            }

            if (consecutiveFlowers == k) 
            {  // If we have k consecutive flowers
                numOfBouquets++;
                consecutiveFlowers = 0;  // Start new bouquet
            }
        }

        return numOfBouquets;
    }

    // Binary search to find the minimum days to form m bouquets
    int minDays(vector<int>& bloomDay, int m, int k) 
    {
        int minDays = *min_element(bloomDay.begin(), bloomDay.end());
        int maxDays = *max_element(bloomDay.begin(), bloomDay.end());

        int start = minDays;
        int end = maxDays;

        int ansDays = -1;

        while (start <= end) 
        {
            int mid = start + (end - start) / 2;

            if (getNumOfBouquets(bloomDay, mid, k) >= m) 
            {
                ansDays = mid;  // A valid solution, try to find a smaller one
                end = mid - 1;
            } 
            else
            {
                start = mid + 1;  // Need more days, try later
            }
        }

        return ansDays;
    }
};
