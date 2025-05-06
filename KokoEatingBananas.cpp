class Solution {
public:
    // Calculate total hours needed to eat all bananas at a given eating speed
    long long calculateHoursAtSpeed(const vector<int>& bananaPiles, int eatingSpeed) 
    {
        long long totalHours = 0;
        for (int bananas : bananaPiles) 
        {
            // ceil(bananas / eatingSpeed) → using integer math
            totalHours += (bananas / eatingSpeed) + (bananas % eatingSpeed != 0);
        }
        return totalHours;
    }

    // Find the minimum integer eating speed such that Koko can finish all piles within 'maxHours'
    int minEatingSpeed(vector<int>& bananaPiles, int maxHours) {
        int minSpeed = 1;             // Lowest possible eating speed
        int maxSpeed = 1e9;           // Upper bound based on constraints
        int optimalSpeed = maxSpeed;  // Initialize with worst case

        // Binary search to find the minimal valid speed
        while (minSpeed <= maxSpeed)
        {
            int currentSpeed = minSpeed + (maxSpeed - minSpeed) / 2;
            long long requiredHours = calculateHoursAtSpeed(bananaPiles, currentSpeed);

            if (requiredHours > maxHours)
            {
                // Too slow, increase speed
                minSpeed = currentSpeed + 1;
            }
            else
            {
                // Possible to finish in time, try slower speed
                optimalSpeed = currentSpeed;
                maxSpeed = currentSpeed - 1;
            }
        }

        return optimalSpeed;
    }
};
