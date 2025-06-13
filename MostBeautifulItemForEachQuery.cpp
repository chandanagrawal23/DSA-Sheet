class Solution
{
public:
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries)
    {
        sort(items.begin(), items.end()); // Sort by price

        int n = items.size();
        vector<int> prefixMax(n);
        prefixMax[0] = items[0][1];

        for (int i = 1; i < n; i++)
        {
            prefixMax[i] = max(prefixMax[i - 1], items[i][1]); // Build prefix max beauty array
        }

        vector<int> ans;

        for (int price : queries)
        {
            int left = 0, right = n - 1;
            int index = -1;

            // Binary search to find the last item with price <= query
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (items[mid][0] <= price)
                {
                    index = mid;
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }

            if (index == -1)
                ans.push_back(0); // No item affordable
            else
                ans.push_back(prefixMax[index]); // Get max beauty from prefix array
        }

        return ans;
    }
};

/*
Approach:
- Sort items based on price.
- Create prefixMax array where prefixMax[i] = max beauty from index 0 to i.
- For each query, binary search to find the rightmost item with price <= query.
- Use prefixMax to get the maximum beauty up to that point.

Time: O(N log N + Q log N), where N = number of items, Q = number of queries
Space: O(N) for prefixMax array
*/
