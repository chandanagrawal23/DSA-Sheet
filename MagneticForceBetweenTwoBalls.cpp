#include <iostream>
#include <vector>
#include <algorithm>

class Solution 
{
public:
    int maxDistance(vector<int>& positions, int numBalls)
    {
        // Sort the basket positions
        sort(positions.begin(), positions.end());

        int low = 1;  // minimum possible magnetic force
        int high = positions.back() - positions.front();  // maximum possible magnetic force
        int maxForce = 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (canPlaceBallsWithMinForce(positions, mid, numBalls)) 
            {
                maxForce = mid;
                low = mid + 1;  // Try for a larger force
            } 
            else
            {
                high = mid - 1;  // Try for a smaller force
            }
        }
        return maxForce;
    }

private:
    bool canPlaceBallsWithMinForce(vector<int>& positions, int minForce, int numBalls) 
    {
        int placedBalls = 1;  // Place the first ball at the first basket position
        int lastPosition = positions[0];

        for (int i = 1; i < positions.size(); ++i)
        {
            if (positions[i] - lastPosition >= minForce) 
            {
                placedBalls++;
                lastPosition = positions[i];  // Update the last position where a ball is placed
            }
            if (placedBalls >= numBalls)
            {
                return true;  // Successfully placed all balls
            }
        }
        return false;  // Couldn't place all balls with the given minimum force
    }
};
