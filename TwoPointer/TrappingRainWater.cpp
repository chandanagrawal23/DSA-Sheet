// Forr this problem there are 5 approaches , we are discussing 4 here, 5th one is MonoStack Based

//1. Brute Force
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        int water = 0;

        for (int i = 1; i < n - 1; i++)
        {
            int leftMax = 0, rightMax = 0;

            // Find max height to the left of i
            for (int j = i; j >= 0; j--)
            {
                leftMax = max(leftMax, height[j]);
            }

            // Find max height to the right of i
            for (int j = i; j < n; j++)
            {
                rightMax = max(rightMax, height[j]);
            }

            // Water trapped = min(leftMax, rightMax) - height[i]
            water += min(leftMax, rightMax) - height[i];
        }

        return water;
    }
};

/*
Approach 1: Brute Force
--------------------------------------
- For each index `i`, we find the tallest bar to its left and right.
- Water trapped at position `i` depends on the **minimum of the two heights**.
- If both sides are tall, water can pool up to the height of the shorter wall.
- The current bar height `height[i]` takes up that much space, so:
    water += min(leftMax, rightMax) - height[i]

Time: O(n^2) — For each index, we traverse the array twice.
Space: O(1) — No extra space used.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////

// Approach 2: Prefix and Suffix Arrays
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
            return 0;

        vector<int> leftMax(n), rightMax(n);

        // Build left max array
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++)
        {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        // Build right max array
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int water = 0;
        for (int i = 0; i < n; i++)
        {
            // Use precomputed max heights to find trapped water
            water += min(leftMax[i], rightMax[i]) - height[i];
        }

        return water;
    }
};

/*
Approach 2: Prefix & Suffix Arrays
--------------------------------------
- Precompute the maximum height to the left and right of each bar.
- Instead of searching every time like brute force, use pre-filled arrays.
- For each i, trapped water is:
    water += min(leftMax[i], rightMax[i]) - height[i]

Time: O(3n) = O(n)
Space: O(2n) — for leftMax and rightMax arrays.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////

// Approach 3: Prefix Variable + Suffix Array
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
            return 0;

        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];

        // Precompute right max array only
        for (int i = n - 2; i >= 0; i--)
        {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int leftMax = 0;
        int water = 0;

        for (int i = 0; i < n; i++)
        {
            leftMax = max(leftMax, height[i]); // compute leftMax on the go
            water += min(leftMax, rightMax[i]) - height[i];
        }

        return water;
    }
};

/*
Approach 3: Prefix Variable + Suffix Array
--------------------------------------
- Instead of storing both leftMax and rightMax arrays, we use a single variable for leftMax.
- Still precompute rightMax array to avoid O(n) scans.
- Saves space while keeping linear time.

Time: O(n)
Space: O(n) — Only rightMax array used.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////

//Approach 4 : Two Pointers ( Nice one )
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n <= 2)
        {
            return 0;
        }

        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;

        while (left < right)
        {
            if (height[left] < height[right])
            {
                if (height[left] >= leftMax)
                {
                    leftMax = height[left]; // update max on left side
                }
                else
                {
                    water += leftMax - height[left]; // water trapped = leftMax - current height
                }
                left++;
            }
            else
            {
                if (height[right] >= rightMax)
                {
                    rightMax = height[right]; // update max on right side
                }
                else
                {
                    water += rightMax - height[right]; // water trapped = rightMax - current height
                }
                right--;
            }
        }

        return water;
    }
};

/*
Approach (Two Pointers - Optimized):

- The amount of water that can be trapped at index `i` is:
      min(max height to the left, max height to the right) - height[i]

- Instead of using extra space for leftMax and rightMax arrays,
  we use two pointers (left and right) and keep track of leftMax and rightMax on the fly.

- At each step:
    - Whichever side is smaller (height[left] or height[right]), we move that pointer.
    - Because that side is the bottleneck, we can be sure about the min(leftMax, rightMax).
    - If current height < max on that side, water can be trapped.

- Why water += min(leftMax, rightMax) - height[i]?
    - This formula represents: max height that can contain water - actual height at current position.
    - So it gives the height of the water trapped above the current cell.

Dry Run on height = [0,1,0,2,1,0,1,3,2,1,2,1]

Steps:
- left = 0, right = 11, water = 0
- height[left] < height[right] → move left
  → update leftMax = 0
- left = 1, height[1]=1 → update leftMax = 1
- left = 2, height[2]=0 → water += 1-0 = 1
- left = 3, height[3]=2 → update leftMax = 2
- left = 4, height[4]=1 → water += 2-1 = 1
- left = 5, height[5]=0 → water += 2-0 = 2
- left = 6, height[6]=1 → water += 2-1 = 1
- left = 7, height[7]=3 → update leftMax = 3
- right side becomes the limiting factor and continues...

Total trapped water = 6

Time Complexity: O(N)
- Each index is visited once by either left or right pointer.

Space Complexity: O(1)
- No extra arrays used.
*/

