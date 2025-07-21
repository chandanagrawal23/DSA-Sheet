// There are three approaches [ Brute , Jump , and stack ] , learn all three

// Approach 1: Basic Brute force try to extend from each "i" to its left and right while possible
class Solution 
{
public:
    int largestRectangleArea(vector<int>& heights) 
    {
        int n = heights.size();

        vector<int> lessFromLeft(n);   // Index of first smaller bar to the left
        vector<int> lessFromRight(n);  // Index of first smaller bar to the right

        lessFromLeft[0] = -1;
        lessFromRight[n - 1] = n;

        // Fill lessFromLeft
        for (int i = 1; i < n; i++) 
        {
            int p = i - 1;

            while (p >= 0 && heights[p] >= heights[i]) 
            {
                p--;
            }

            lessFromLeft[i] = p;
        }

        // Fill lessFromRight
        for (int i = n - 2; i >= 0; i--) 
        {
            int p = i + 1;

            while (p < n && heights[p] >= heights[i]) 
            {
                p++;
            }

            lessFromRight[i] = p;
        }

        // Compute max area using left and right boundaries
        int maxArea = 0;

        for (int i = 0; i < n; i++) 
        {
            int width = lessFromRight[i] - lessFromLeft[i] - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

/*
APPROACH:
---------
- For each bar, find:
    - The index of the first smaller bar to its **left** (`lessFromLeft`)
    - The index of the first smaller bar to its **right** (`lessFromRight`)
- Then, use the formula:
      width = lessFromRight[i] - lessFromLeft[i] - 1
      area  = height[i] * width
- Take maximum of all such areas.

CURRENT METHOD:
---------------
- We use a linear scan (`p++` and `p--`) to find these smaller bars.
- In the worst case (like monotonic heights), this gives O(n²) time.

OPTIMIZATION:
-------------
- Instead of scanning linearly for smaller elements, we can **jump** using precomputed results (`lessFromLeft[p]`, `lessFromRight[p]`) — like union-find.
- This optimization reduces time complexity to **O(n)** overall by avoiding repeated work.

*/

// Approach 2 : Extension to approach 1, simply use the previous result aka, jump directly to the index

class Solution 
{
public:
    int largestRectangleArea(vector<int>& heights) 
    {
        int n = heights.size();

        vector<int> lessFromLeft(n);   // Index of first smaller bar to the left
        vector<int> lessFromRight(n);  // Index of first smaller bar to the right

        lessFromLeft[0] = -1;
        lessFromRight[n - 1] = n;

        // Fill lessFromLeft
        for (int i = 1; i < n; i++) 
        {
            int p = i - 1;

            while (p >= 0 && heights[p] >= heights[i]) 
            {
                p = lessFromLeft[p]; // Jump to previously computed left boundary
            }

            lessFromLeft[i] = p;
        }

        // Fill lessFromRight
        for (int i = n - 2; i >= 0; i--) 
        {
            int p = i + 1;

            while (p < n && heights[p] >= heights[i]) 
            {
                p = lessFromRight[p]; // Jump to previously computed right boundary
            }

            lessFromRight[i] = p;
        }

        // Compute max area using left and right boundaries
        int maxArea = 0;

        for (int i = 0; i < n; i++) 
        {
            int width = lessFromRight[i] - lessFromLeft[i] - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

/*
APPROACH:
---------
- This solution precomputes the first smaller bar to the left and right for every bar in the histogram.
- It uses a trick to "jump" across known results instead of a stack.

- For bar at index `i`, the largest rectangle that can be made with `heights[i]` as the shortest bar spans:
      from index `lessFromLeft[i] + 1` to `lessFromRight[i] - 1`.

- So width = lessFromRight[i] - lessFromLeft[i] - 1

✅ DRY RUN:
Input: heights = [2, 1, 5, 6, 2, 3]
Indices:          0  1  2  3  4  5

Step 1: Compute lessFromLeft
================================
This stores the index of the first bar to the left that is strictly smaller than the current bar.

Initialize: lessFromLeft[0] = -1

i = 1 → heights[1] = 1
       ← compare with heights[0] = 2 (not < 1), jump to lessFromLeft[0] = -1
       → lessFromLeft[1] = -1

i = 2 → heights[2] = 5
       ← compare with heights[1] = 1 (1 < 5), so lessFromLeft[2] = 1

i = 3 → heights[3] = 6
       ← compare with heights[2] = 5 (5 < 6), so lessFromLeft[3] = 2

i = 4 → heights[4] = 2
       ← compare with heights[3] = 6 → jump to lessFromLeft[3] = 2
       ← heights[2] = 5 → jump to lessFromLeft[2] = 1
       ← heights[1] = 1 (1 < 2) → lessFromLeft[4] = 1

i = 5 → heights[5] = 3
       ← compare with heights[4] = 2 (2 < 3) → lessFromLeft[5] = 4
       
➡️ Final lessFromLeft = [-1, -1, 1, 2, 1, 4]

Step 2: Compute lessFromRight
================================

This stores the index of the first bar to the right that is strictly smaller than the current bar.

Initialize: lessFromRight[5] = 6

i = 4 → heights[4] = 2
       → compare with heights[5] = 3 (not < 2), jump to lessFromRight[5] = 6
       → no smaller found, so lessFromRight[4] = 6

i = 3 → heights[3] = 6
       → compare with heights[4] = 2 (2 < 6) → lessFromRight[3] = 4

i = 2 → heights[2] = 5
       → compare with heights[3] = 6 (not < 5), jump to lessFromRight[3] = 4
       → heights[4] = 2 (2 < 5) → lessFromRight[2] = 4

i = 1 → heights[1] = 1
       → heights[2] = 5 (not < 1) → jump to 4 → heights[4] = 2 (not < 1) → jump to 6
       → no smaller → lessFromRight[1] = 6

i = 0 → heights[0] = 2
       → heights[1] = 1 (1 < 2) → lessFromRight[0] = 1
➡️ Final lessFromRight = [1, 6, 4, 4, 6, 6]

Step 3: Compute Max Area
========================
i = 0 → height = 2
        width = 1 - (-1) - 1 = 1
        area = 2 * 1 = 2

i = 1 → height = 1
        width = 6 - (-1) - 1 = 6
        area = 1 * 6 = 6

i = 2 → height = 5
        width = 4 - 1 - 1 = 2
        area = 5 * 2 = 10 ✅

i = 3 → height = 6
        width = 4 - 2 - 1 = 1
        area = 6 * 1 = 6

i = 4 → height = 2
        width = 6 - 1 - 1 = 4
        area = 2 * 4 = 8

i = 5 → height = 3
        width = 6 - 4 - 1 = 1
        area = 3 * 1 = 3
        
➡️ Maximum Area = 10

TIME COMPLEXITY:
----------------
- O(n) for filling both lessFromLeft and lessFromRight
- O(n) for computing final area

SPACE COMPLEXITY:
-----------------
- O(n) extra space for left and right arrays
*/

// Approach 3 : Use MonoTonic Stack to find "First Lesser Element in left of i" and "First Lesser Element in right of i"

class Solution 
{
public:
    int largestRectangleArea(vector<int>& heights) 
    {
        int n = heights.size();
        vector<int> lessFromLeft(n);   // First smaller bar on the left
        vector<int> lessFromRight(n);  // First smaller bar on the right
        stack<int> st;

        // Fill lessFromLeft using monotonic increasing stack
        for (int i = 0; i < n; i++) 
        {
            while (!st.empty() && heights[st.top()] >= heights[i]) 
            {
                st.pop();
            }

            lessFromLeft[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        // Clear stack for reuse
        while (!st.empty()) st.pop();

        // Fill lessFromRight using monotonic increasing stack
        for (int i = n - 1; i >= 0; i--) 
        {
            while (!st.empty() && heights[st.top()] >= heights[i]) 
            {
                st.pop();
            }

            lessFromRight[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // Compute max area
        int maxArea = 0;

        for (int i = 0; i < n; i++) 
        {
            int width = lessFromRight[i] - lessFromLeft[i] - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

/*
APPROACH:
---------
- For each bar, we want to find:
    1. First smaller element to the left → `lessFromLeft`
    2. First smaller element to the right → `lessFromRight`

- Use a monotonic increasing stack to compute both in O(n) time:
    - While the current bar is smaller than the stack top, pop the stack.
    - The top of the stack gives us the nearest smaller element.

- Once boundaries are found:
    width = lessFromRight[i] - lessFromLeft[i] - 1
    area = heights[i] * width

- Track the maximum area among all bars.

TIME: O(n)
SPACE: O(n)
*/
