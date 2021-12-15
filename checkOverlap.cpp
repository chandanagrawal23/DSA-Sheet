class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        // Find the closest point to the circle within the rectangle
        int closestX = clamp(x_center, x1, x2);
        int closestY = clamp(y_center, y1, y2);

        // Calculate the distance between the circle's center and this closest point
        int distanceX = x_center - closestX;
        int distanceY = y_center - closestY;

        // If the distance is less than the circle's radius, an intersection occurs
        int distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
        return distanceSquared <= (radius * radius);
    }
    int clamp(int centerCoordinate, int mini, int maxi) {
        return max(mini, min(maxi, centerCoordinate));
    }
};
//https://leetcode.com/problems/circle-and-rectangle-overlapping/
