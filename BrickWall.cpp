/*
Approach & Intuition:

We are given a brick wall where each row contains bricks of varying widths,
but all rows sum up to the same total width. Our goal is to draw a vertical
line from top to bottom that crosses the **fewest bricks possible**.

Key Idea:
- The line should ideally go through the **edges** between bricks (not through the bricks themselves).
- For each row, compute all **edge positions** (excluding the rightmost edge).
- Count how many times each edge position appears across all rows.
- The **edge position with the highest frequency** is the best place to draw the line.
- The answer will be: **total number of rows - max frequency of any edge position**.

Why?
Because we avoid crossing bricks in the rows where the edge is present,
and in the remaining rows, the line will cross one brick each.
*/

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) 
    {
        int n = wall.size();

        // Step 1: For each row, calculate the prefix sums (brick edges except the last edge)
        vector<vector<long long>> rowEdges(n); // stores edge positions for each row

        for (int i = 0; i < n; ++i) 
        {
            long long edge = 0;
            // do not take last brick (not allowed to draw along the right edge)
            for (int j = 0; j < (int)wall[i].size() - 1; ++j) 
            {
                edge += 1ll * wall[i][j];
                rowEdges[i].push_back(edge);  // record internal brick edge
            }
        }

        // Step 2: Count the frequency of each edge position
        unordered_map<long long, int> edgeFreq;
        int maxFreq = 0;

        for (const auto& edges : rowEdges) 
        {
            for (long long pos : edges) 
            {
                edgeFreq[pos]++;
                maxFreq = max(maxFreq, edgeFreq[pos]);
            }
        }

        // Step 3: Answer = total rows - max frequency of aligned edge
        // We want to draw the vertical line through the edge that occurs most frequently
        // This way, we avoid crossing bricks in those rows
        // The rest of the rows (n - maxFreq) are where the line crosses bricks
        return n - maxFreq;
    }
};
