class Solution
{
public:
    // Count number of pairs with absolute difference less than equal to "dist"
    int countPairsWithMaxDistance(vector<int>& nums, int dist)
    {
        int count = 0, left = 0;
        for (int right = 0; right < nums.size(); ++right)
        {
            while (nums[right] - nums[left] > dist)
                left++;

            count += (right - left);
        }
        return count;
    }

    int smallestDistancePair(vector<int>& nums, int k)
    {
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.back() - nums.front(); // max possible distance between any two elements
        int ans = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            int count = countPairsWithMaxDistance(nums, mid);

            if (count >= k)
            {
                ans = mid;        // potential answer
                right = mid - 1;  // try smaller distance
            }
            else
            {
                left = mid + 1;   // need larger distances
            }
        }

        return ans;
    }
};

/*

Approach:
---------
Goal: Find the k-th smallest absolute difference between all possible pairs in the array.

Steps:
1. Sort the input array.
2. Use binary search on distance value `d` in range [0, max(nums) - min(nums)].
3. For each `mid`, count how many pairs have distance ≤ `mid` using two pointers.
   - For each `right`, move `left` forward until `nums[right] - nums[left] <= mid`
   - The number of such pairs ending at `right` is (right - left)
   - Sum all such counts.
4. If total pairs ≥ k, `mid` is a candidate → try smaller → right = mid - 1
5. Else, search larger → left = mid + 1

Why Binary Search Works:
- The number of valid pairs is monotonic with increasing distance.
- So we can binary search on answer space.

Time: O(n log n + n log(max_dist))  
Space: O(1) auxiliary (not counting sort)

*/
