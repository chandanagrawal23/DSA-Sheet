// Sweep Line
class Solution
{
public:
    int brightestPosition(vector<vector<int>> &lights)
    {
        map<int, int> sweepEvents;

        // Step 1: Build sweep line events
        for (auto &light : lights)
        {
            int lightPos = light[0];
            int rangeOfLight = light[1];

            int leftPos = lightPos - rangeOfLight;
            int rightPos = lightPos + rangeOfLight;

            // At leftPos, brightness starts (+1)
            sweepEvents[leftPos] += 1;

            // Just after rightPos, brightness ends (-1)
            sweepEvents[rightPos + 1] -= 1;
        }

        int maxBrightness = 0;
        int currBrightness = 0;
        int bestPosition = INT_MAX;

        // Step 2: Process the sweep line in order of positions
        for (auto &[pos, delta] : sweepEvents)
        {
            currBrightness += delta;

            // Update maximum brightness and position
            if (currBrightness > maxBrightness)
            {
                maxBrightness = currBrightness;
                bestPosition = pos;
            }
            else if (currBrightness == maxBrightness)
            {
                bestPosition = min(bestPosition, pos); // pick smaller position in case of tie
            }
        }

        return bestPosition;
    }
};

/*
🧠 Approach: Line Sweep using Ordered Map

1. Every light [pos, range] lights up the interval [pos - range, pos + range].
   We treat this as a range update using difference array logic.

2. For each light:
   - Add +1 at (pos - range)
   - Add -1 at (pos + range + 1)
   This means: brightness increases at the start and decreases just after the end.

3. Store all these changes in a map<int, int> (auto-sorted by position).

4. Traverse all positions in increasing order:
   - Maintain currentBrightness by adding deltas from the map.
   - Track the maximum brightness and update bestPosition accordingly.
   - If brightness is tied, take the smaller position.

5. Return the position with maximum brightness (smallest in case of tie).

 Time Complexity: O(N log N) due to map insertions and traversal
 Space Complexity: O(N) for storing all brightness change events

*/
