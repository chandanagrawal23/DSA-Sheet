class Solution  // O(n^2 * log k)
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size();
        priority_queue<int> maxHeap; // Maintain max heap of size k

        for (int r = 0; r < m; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                maxHeap.push(matrix[r][c]);       // Add current element
                
                if (maxHeap.size() > k) 
                        maxHeap.pop(); // Keep heap size ≤ k
            }
        }
        return maxHeap.top(); // Top of max heap = kth smallest
    }
};

/*
Approach:
- Traverse all elements and maintain a max heap of size k.
- At the end, the top of the heap is the kth smallest.

Time: O(n^2 * log k)
Space: O(k)
*/

//=====================================================================================================================

class Solution  // O(k * log k)
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size(), ans;

        // Min heap of {value, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<>> minHeap;

        // Insert first element from each of the first min(m, k) rows
        for (int r = 0; r < min(m, k); ++r)
        {
            minHeap.push({matrix[r][0], r, 0});
        }

        // Extract min k times
        for (int i = 1; i <= k; ++i)
        {
            auto top = minHeap.top(); minHeap.pop();
            int r = top[1], c = top[2];
            ans = top[0]; // This is the ith smallest

            // Push next element in the same row
            if (c + 1 < n)
            {
                minHeap.push({matrix[r][c + 1], r, c + 1});
            }
        }
        return ans;
    }
};

/*
Approach:
- Use a min heap to simulate a k-way merge of sorted rows.
- Start with the first element of each row, pop the smallest, and push the next element from the same row.

Time: O(k * log k)
Space: O(k)
*/
