class Solution
{
public:
    int rangeSum(vector<int> &nums, int n, int left, int right)
    {
        const int mod = 1e9 + 7;
        int ans = 0;

        // Min heap stores: {current sum, next index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        // Initialize with single-element subarrays
        for (int i = 0; i < n; i++)
        {
            pq.push({nums[i], i + 1}); // sum = nums[i], next index = i+1
        }

        // Extract subarray sums in sorted order
        for (int i = 1; i <= right; i++)
        {
            auto [sum, idx] = pq.top();
            pq.pop();

            // If within desired range, add to answer
            if (i >= left)
            {
                ans = (ans + sum) % mod;
            }

            // If possible, extend the subarray
            if (idx < n)
            {
                pq.push({sum + nums[idx], idx + 1});
            }
        }

        return ans;
    }
};

/*
Approach: Min Heap (Like Merge K Sorted Lists)
==============================================

 Goal:
--------
You're given an array `nums` and need to compute the sum of all subarray sums
(between the `left`-th and `right`-th smallest ones), **without generating all of them**.

 Brute Force:
---------------
- Generate all O(n²) subarray sums
- Sort the list
- Sum the elements from index `left-1` to `right-1`
Too slow for large inputs.

 Optimized Idea (Using Min Heap):
-----------------------------------
- Instead of generating and sorting all subarray sums,
  we simulate the process of generating them in **sorted order** using a **min-heap**.

 Key Observation:
-------------------
- Every subarray starting from index `i` can be extended by one element at a time.
- So from `nums[i]`, we can generate a sorted stream of subarray sums: 
  → nums[i], nums[i]+nums[i+1], nums[i]+nums[i+1]+nums[i+2], ...

 Steps:
---------
1. Initialize a min-heap with `{nums[i], i+1}` for all `i = 0` to `n-1`.
   → Each heap entry represents a subarray sum starting at `i`, ending at `i`.

2. Repeat `right` times:
   - Pop the smallest current sum.
   - If this is within range [left, right], add to answer.
   - If the subarray can be extended (`j < n`), push its next version:
       → new_sum = current_sum + nums[j]
       → j = next index after current

 Analogy:
-----------
Imagine you're standing in front of a sorted infinite stream of numbers (coming from merging all subarrays).

You want the sum of all numbers from the 5th to the 8th in that stream.

So:

You can’t skip the first 4

You must process the first 8

And only keep the 5th to 8th

Hence you need to pop the smallest subarray sums from heap up to right times.


Why This Works:
---------------
- This is like merging K sorted lists (each list is a stream of growing subarrays from nums[i])
- Heap ensures you always process the next smallest sum
- Efficiently avoids storing all O(n²) sums

Some more explaination...
Suppose nums=[1, 2, 3], the possible continous subarrays and their sums are:
[1], [1, 2], [1, 2, 3] => [1, 3, 6]
[2], [2, 3] => [2, 5]
[3] => [3]
As you can see, those sums are constructed in this way so that they are sorted. What we need from now on is very similiar to Merge K Sorted Lists.

 Time Complexity:
-------------------
- O(right * log n) — heap stores at most n elements

 Space Complexity:
--------------------
- O(n) — for the heap

*/

