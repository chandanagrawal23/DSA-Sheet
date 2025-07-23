class Solution
{
public:
    // same as https://leetcode.com/problems/largest-rectangle-in-histogram/
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

    int maximalRectangle(vector<vector<char>> &matrix)
    {
        if (matrix.empty() || matrix[0].empty())
        {
            return 0;
        }

        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;

        for (int i = 0; i < m; ++i)
        {
            // Build histogram for each row
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    heights[j] += 1;
                }
                else
                {
                    heights[j] = 0;
                }
            }

            // Compute largest rectangle in histogram using monotonic stack
            maxArea = max(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }
};

/*
Approach (Optimized using Monotonic Stack):

1. Treat each row as the base of a histogram:
   - Convert the matrix into height arrays row by row.
     If matrix[i][j] == '1', then increment heights[j] by 1 (carry the count).
     If matrix[i][j] == '0', reset heights[j] to 0.

   For example:
   Row 0:    ["1","0","1","0","0"]     => heights = [1,0,1,0,0]
   Row 1:    ["1","0","1","1","1"]     => heights = [2,0,2,1,1]
   Row 2:    ["1","1","1","1","1"]     => heights = [3,1,3,2,2]
   Row 3:    ["1","0","0","1","0"]     => heights = [4,0,0,3,0]

2. For each row (height array), calculate the largest rectangle in histogram:
   - Use a monotonic increasing stack to find:
     - The nearest smaller bar to the left (left boundary)
     - The nearest smaller bar to the right (right boundary)
   - Width of rectangle = right - left + 1
   - Area = height * width

3. Track maxArea as the maximum among all histograms derived from matrix rows.

Time Complexity: O(m * n)
- Each cell is processed once per row, and each bar is pushed and popped at most once.

Space Complexity: O(n)
- Extra space used for histogram height, left, right arrays, and stack.
*/
