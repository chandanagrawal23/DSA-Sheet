class Solution {
public:
    bool checkOverlap(int radius, int circleX, int circleY, int rectLeft, int rectBottom, int rectRight, int rectTop) {
        // Step 1: Find the closest X-coordinate inside the rectangle to the circle's center X
        // If circleX is within [rectLeft, rectRight], it stays the same
        // If circleX is to the left of the rectangle, it gets clamped to rectLeft
        // If circleX is to the right of the rectangle, it gets clamped to rectRight
        int nearestX = clampToRange(circleX, rectLeft, rectRight);

        // Step 2: Similarly, clamp the circle's Y-coordinate to get the closest Y inside the rectangle
        int nearestY = clampToRange(circleY, rectBottom, rectTop);

        // Step 3: Calculate how far the circle's center is from this closest point on the rectangle
        int deltaX = circleX - nearestX;
        int deltaY = circleY - nearestY;

        // Step 4: Use Pythagoras to check if this point is within the circle's radius
        // (deltaX^2 + deltaY^2) ≤ radius^2 ⇒ overlap
        return deltaX * deltaX + deltaY * deltaY <= radius * radius;
    }

private:
    // Helper function to clamp a coordinate within rectangle bounds
    // Returns:
    // - coord itself if it's inside the range [minBound, maxBound]
    // - minBound if coord is less than the rectangle’s min
    // - maxBound if coord is more than the rectangle’s max
    int clampToRange(int coord, int minBound, int maxBound) {
        if (coord < minBound) return minBound;   // Circle center is left/below → clamp to min
        if (coord > maxBound) return maxBound;   // Circle center is right/above → clamp to max
        return coord;                            // Circle center is inside the rectangle
    }
};
/*


// Clamp a coordinate inside [minBound, maxBound]
    // This handles three cases:

    /*
        Case 1: Circle center is inside the rectangle — no clamping needed
                 ┌──────────────┐
                 │              │
                 │     ●        │                                                                 ● = circle center
                 │              │
                 └──────────────┘
        
        Case 2: Circle center is to the LEFT of rectangle — clamp to left edge
             ●     ┌──────────────┐
                   │              │
                   │              │                                                               ● = circle center
                   │              │
                   └──────────────┘

        Case 3: Circle center is to the RIGHT of rectangle — clamp to right edge
                   ┌──────────────┐     ●
                   │              │
                   │              │                                                               ● = circle center
                   │              │    
                   └──────────────┘

        Similar logic applies for Y (above or below the rectangle)
    */
