class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) 
    {
        int n = heights.size();
        int totalBricksUsed = 0;

        // Max heap to track all upward climbs where bricks were used
        priority_queue<int> bricksUsed;

        int reach = 0;

        for (; reach < n - 1; reach++) 
        {

            // No effort needed if next building is same or shorter
            if (heights[reach] >= heights[reach + 1]) 
            {
                continue;
            }

            // Need to climb: calculate height difference
            int diff = heights[reach + 1] - heights[reach];

            // Prefer using bricks (greedy), push this climb to heap
            if (totalBricksUsed + diff <= bricks) 
            {
                totalBricksUsed += diff;
                bricksUsed.push(diff);
            }
            else if (ladders > 0) 
            {
                // Bricks not sufficient, but we have ladders

                // Check if we previously used bricks on a larger climb
                // If yes, replace that big brick usage with a ladder
                // and use current smaller climb with bricks (cheaper)
                if (!bricksUsed.empty() && bricksUsed.top() > diff) 
                {
                    int mostBrickUsed = bricksUsed.top(); // biggest climb so far (via bricks)

                    // Replace it: subtract that large brick usage
                    totalBricksUsed -= mostBrickUsed;

                    // Add the smaller climb we’re now covering with bricks
                    totalBricksUsed += diff;

                    // Update heap: remove largest and insert current
                    bricksUsed.pop();
                    bricksUsed.push(diff);
                }

                // Use up one ladder (either way)
                ladders--;
            }
            else 
            {
                // No bricks left and no ladders left → can't go further
                break;
            }
        }

        return reach; // Max reachable building index
    }
};

/*

Approach:
==========
- We must climb from left to right across buildings.
- For any descent or flat walk, no resource is needed.
- For each climb (heights[i+1] > heights[i]), we can:
    a) Use bricks
    b) Use ladder

Greedy Choice:
--------------
- Use bricks first and push every climb diff to a max-heap.
- If total bricks exceed limit and we have a ladder,
  we convert the largest previous brick usage into a ladder use.

Why swap bricks with ladder (when bricksUsed.top() > diff)?
→ So that we use **bricks on smaller climbs** and **ladders on bigger climbs**.
This ensures we save bricks for many small steps instead of wasting them on large ones.

Key Observations:
-----------------
- Max-heap stores all climbs covered by bricks.
- When out of bricks:
    - If the largest previous climb (via bricks) > current climb
      → We swap (ladder on big one, bricks on small one).
    - Otherwise, just use ladder directly.

- Once we can neither climb using bricks nor ladders, we stop.

Time:  O(n log n) — push/pop to max-heap
Space: O(n)       — heap to store brick-used climbs

*/
