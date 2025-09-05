// ------------------ Approach 1 : Brute Force ------------------
class Solution1
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        int n = baskets.size();
        vector<bool> used(n, false);
        int unplaced = 0;

        for (int fruit : fruits)
        {
            bool placed = false;
            for (int i = 0; i < n; i++)
            {
                if (!used[i] && baskets[i] >= fruit)
                {
                    used[i] = true; // assign fruit to basket
                    placed = true;
                    break;
                }
            }
            if (!placed)
                unplaced++;
        }
        return unplaced;
    }
};

/*
-------------------- APPROACH 1 (Brute Force) --------------------
1. For each fruit, scan baskets from left to right.
2. Pick the first unused basket with capacity >= fruit.
3. Mark basket as used.
4. If none found, count fruit as unplaced.

✔ Very simple but inefficient.
Time Complexity  : O(n^2) in worst case
Space Complexity : O(n)
---------------------------------------------------
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ------------------ Approach 2 : SQRT Decomposition ------------------
class Solution3
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        int n = baskets.size();
        int blockSize = sqrt(n);
        int totalBlocks = (n + blockSize - 1) / blockSize;

        int unplacedCount = 0;

        // Precompute max capacity per block
        vector<int> blockMax(totalBlocks, 0);
        for (int i = 0; i < n; i++)
            blockMax[i / blockSize] = max(blockMax[i / blockSize], baskets[i]);

        for (int fruit : fruits)
        {
            bool placed = false;

            // check block by block
            for (int block = 0; block < totalBlocks; block++)
            {
                if (blockMax[block] < fruit)
                    continue; // no basket in this block can fit

                // scan inside block
                int newMax = 0;
                bool used = false;

                for (int j = 0; j < blockSize; j++)
                {
                    int idx = block * blockSize + j;
                    if (idx < n)
                    {
                        if (!used && baskets[idx] >= fruit)
                        {
                            baskets[idx] = 0; // assign basket
                            used = true;
                        }
                        newMax = max(newMax, baskets[idx]);
                    }
                }
                blockMax[block] = newMax;
                placed = true;
                break;
            }

            if (!placed)
                unplacedCount++;
        }
        return unplacedCount;
    }
};

/*
-------------------- APPROACH 2 (SQRT Decomposition) --------------------
1. Divide baskets into √n sized blocks.
2. Maintain maximum basket capacity for each block.
3. For each fruit:
   - Find the first block where blockMax >= fruit.
   - Scan that block linearly to assign fruit.
   - Update blockMax after placement.
   - If no suitable block found, mark as unplaced.

✔ Optimized structure to avoid scanning full array every time.
Time Complexity  : O(n * √n)
Space Complexity : O(n)
---------------------------------------------------
*/
