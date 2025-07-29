class Solution
{
public:
    vector<int> resultsArray(vector<vector<int>> &queries, int k)
    {
        priority_queue<int> maxHeap; // Max heap to store top-k closest distances
        int n = queries.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++)
        {
            int dist = abs(queries[i][0]) + abs(queries[i][1]); // Manhattan distance
            maxHeap.push(dist);

            if (maxHeap.size() > k)
            {
                maxHeap.pop(); // Keep only k smallest distances
            }

            // If k distances seen, top is the k-th closest
            result[i] = (maxHeap.size() == k) ? maxHeap.top() : -1;
        }

        return result;
    }
};

/*

Approach:
==========
- Use a max heap to keep track of k closest obstacle distances (by Manhattan distance).
- For each query, push abs(x) + abs(y) into the heap.
- If heap size exceeds k, pop the farthest one.
- At each step:
   - If we’ve seen fewer than k points, return -1
   - Else, top of the max heap is the k-th closest

Time: O(n log k), Space: O(k)

*/
