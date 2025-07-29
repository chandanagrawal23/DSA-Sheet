class Solution
{
public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k)
    {
        vector<pair<double, int>> workers;

        // Step 1: Calculate wage-to-quality ratio for each worker
        for (int i = 0; i < quality.size(); ++i)
        {
            double ratio = (double)wage[i] / quality[i];
            workers.push_back({ratio, quality[i]});
        }

        // Step 2: Sort workers based on increasing ratio
        sort(workers.begin(), workers.end());

        // Max-heap to maintain k smallest qualities
        priority_queue<int> maxHeap;
        double minCost = DBL_MAX, totalQuality = 0;

        // Step 3: Try hiring the first k workers with the current ratio , we will pop (n-k) times from max heap to behave like a min heap
        // pop n-k times from min heap and then the top element is our  kthm min element in last 
        for (auto &[ratio, q] : workers)
        {
            totalQuality += q;
            maxHeap.push(q);

            // if size is greater than k remove the top max element
            if (maxHeap.size() > k)
            {
                totalQuality -= maxHeap.top();
                maxHeap.pop();
            }
            // if size is k , that means top element is k'th minimum element so find min
            if (maxHeap.size() == k)
            {
                minCost = min(minCost, totalQuality * ratio);
            }
        }

        return minCost;
    }
};
/*
Approach: Greedy + Heap (O(n log n))
====================================

We are given:
- Each worker has a `quality[i]` and a minimum wage `wage[i]`
- We must hire exactly `k` workers such that:
    1. They all get paid using the **same wage-to-quality ratio**
    2. Each one gets at least their minimum wage

Goal: Minimize the total cost to hire k such workers

Key Insight:
------------
- If a group is paid using ratio `R`, each worker will get paid `R * quality[i]`
- For it to be valid: `R >= wage[i] / quality[i]` for each selected worker
- So for a group, the **maximum ratio among them** will determine the payment

Steps:
------
1. Compute the ratio `wage[i] / quality[i]` for each worker
2. Sort all workers by increasing ratio
3. Use a max-heap to maintain the k smallest-quality workers seen so far
4. At each step:
   - Add current worker to heap
   - If heap size > k → remove worker with largest quality (to minimize cost)
   - If heap size == k → check cost: `ratio * sum_of_qualities`
   - Update answer accordingly

Why This Works:
---------------
- We sort workers by ratio so we are **guaranteeing the ratio constraint**
- Among those, we try to pick k workers with **lowest quality sum** to minimize cost

Time:  O(n log n) due to sorting and heap operations
Space: O(k) for the heap
*/
