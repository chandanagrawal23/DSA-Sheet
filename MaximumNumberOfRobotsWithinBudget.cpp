/*
There are 3 approaches
1. Dynamic Sliding Window + Multiset ( N-logN)
2. Dynamic Sliding Window + Heap ( N-logN)
3. Dynamic Sliding Window + Monotonic Deque ( N ) , IMPORTANT , but learn above 2 first
*/

// approach 1 Dynamic Sliding Window + Multiset ( N-logN)
class Solution
{
public:
    typedef long long ll;

    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget)
    {
        multiset<int> maxCharge;     // ascending order , multiset.begin() gives minimum value , and multiset.rbegin() gives maxiimum value
        ll windowSum = 0;            
        ll left = 0, right = 0;      
        ll maxRobots = 0;
        ll n = chargeTimes.size();

        while (right < n)
        {
            // Expand window to include current robot
            windowSum += runningCosts[right];
            maxCharge.insert(chargeTimes[right]);
            ++right;

            // Compute total cost: max(chargeTimes) + window_size * sum(runningCosts)
            ll totalCost = *maxCharge.rbegin() + (right - left) * windowSum;

            // Shrink window from left if budget is exceeded
            while (totalCost > budget)
            {
                windowSum -= runningCosts[left];

                maxCharge.erase(maxCharge.find(chargeTimes[left]));

                ++left;
                
                totalCost = 0;

                if(!maxCharge.empty())
                    totalCost =  *maxCharge.rbegin() + (right - left) * windowSum;
            }

            // Update answer with max number of robots in valid budget window
            maxRobots = max(maxRobots, right - left);
        }

        return maxRobots;
    }
};

/*

Approach:
---------
We are given:
- chargeTimes[i]: One-time cost for selecting the i-th robot.
- runningCosts[i]: Per-robot cost for every unit time.

For any window [i, j], the total cost is:
    max(chargeTimes[i..j]) + (j - i + 1) * sum(runningCosts[i..j])

We need to find the **maximum number of robots** we can run such that this cost ≤ budget.

To solve this:
1. Use a sliding window approach with two pointers `left` and `right`.
2. Track:
   - The **maximum chargeTime** in the window using a `multiset`:
     → `*maxCharge.rbegin()` gives the largest value in the window.
   - The **sum of runningCosts** in the window using `windowSum`.

3. For each `right`, try to include that robot in the window.
   - If total cost exceeds budget, remove robots from the left side of the window.

4. At every step, update the maximum window size (`right - left`) that stays under budget.

Why multiset?
-------------
- It maintains sorted order.
- Gives `O(log n)` insertion/deletion and `O(1)` access to max using `rbegin()`.

Edge Cases:
-----------
- `multiset.erase(multiset.find(x))` is used instead of erase(x) to remove **only one occurrence**.

Time Complexity: O(n * log n)
- Each insertion and deletion in multiset is O(log n)
- Each element enters and leaves the window at most once

Space Complexity: O(n)
- multiset may hold up to n elements in the worst case

*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Approach 2. Dynamic Sliding Window + Heap ( N-logN)
class Solution
{
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget)
    {
        int n = chargeTimes.size();
        long long totalRunningCost = 0;  // Sum of runningCosts in current window
        int left = 0, maxRobots = 0;

        // Max-heap to track maximum chargeTime in current window
        // Each entry is {chargeTime, index}
        priority_queue<pair<int, int>> maxHeap;

        for (int right = 0; right < n; ++right)
        {
            totalRunningCost += runningCosts[right];
            maxHeap.push({chargeTimes[right], right});

            // Total cost = max(chargeTimes) + windowSize * sum(runningCosts)
            long long totalCost = maxHeap.top().first + (long long)(right - left + 1) * totalRunningCost;

            // Shrink window from the left until cost is within budget
            while (totalCost > budget)
            {
                totalRunningCost -= runningCosts[left];

                // Remove stale values from heap that are out of window
                while (!maxHeap.empty() && maxHeap.top().second <= left)
                {
                    maxHeap.pop();
                }

                ++left;

                // Recalculate total cost if heap still has elements
                totalCost = maxHeap.empty() ? 0 : maxHeap.top().first + (long long)(right - left + 1) * totalRunningCost;
            }

            // Update answer with maximum window size
            maxRobots = max(maxRobots, right - left + 1);
        }

        return maxRobots;
    }
};

/*

Approach:
---------
We are given:
- chargeTimes[i]: cost paid once when a robot is selected.
- runningCosts[i]: cost paid per robot per round.

For any window [i, j], the total cost is:
    max(chargeTimes[i..j]) + (j - i + 1) * sum(runningCosts[i..j])

Goal:
→ Find the maximum number of robots you can select in a window such that this cost ≤ budget.

To do this efficiently:
1. Use a **sliding window** with `left` and `right` pointers.
2. Track sum of runningCosts inside the window using a variable `totalRunningCost`.
3. Track max(chargeTimes in window) using a **max-heap** (priority queue).
   - But since the heap can have **stale values** (outside the window), remove them whenever `left` moves forward.
4. If the total cost exceeds the budget, shrink the window from the left.
5. Keep track of the maximum valid window size seen so far.

Why max-heap works:
- Unlike `deque`, which maintains order, we allow duplicates and don't remove on each shift.
- Instead, we lazily remove any stale indices whose position ≤ `left`.

Time Complexity: O(n log n)
- Each index is pushed and popped from the heap at most once.
- Each heap operation is O(log n).

Space Complexity: O(n)
- The heap may store up to n entries in the worst case.

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Approach 3. Dynamic Sliding Window + Monotonic Deque ( N )
class Solution
{
public:
    typedef long long ll;

    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget)
    {
        deque<int> dq;               // Monotonic deque to keep track of max(chargeTimes) in window
        ll left = 0, right = 0;      // Sliding window pointers
        ll windowSum = 0;            // Sum of runningCosts in current window
        ll maxRobots = 0;
        int n = chargeTimes.size();

        while (right < n)
        {
            windowSum += runningCosts[right];

            // Maintain a decreasing deque (index of max chargeTime at front)
            while (!dq.empty() && chargeTimes[dq.back()] <= chargeTimes[right])
            {
                dq.pop_back();
            }
            dq.push_back(right);

            // Calculate total cost in current window
            ll totalCost = chargeTimes[dq.front()] + (right - left + 1) * windowSum;

            // Shrink the window if budget is violated
            while (totalCost > budget)
            {
                // Remove expired max chargeTime index if it's going out of window
                if (dq.front() == left)
                {
                    dq.pop_front();
                }

                windowSum -= runningCosts[left];
                ++left;

                // Recalculate total cost after window adjustment
                totalCost = dq.empty() ? 0 : chargeTimes[dq.front()] + (right - left + 1) * windowSum;
            }

            // Update answer
            maxRobots = max(maxRobots, right - left + 1);
            ++right;
        }

        return maxRobots;
    }
};

/*

Approach:
---------
We need to select the largest number of robots such that:

    max(chargeTimes[i to j]) + (j - i + 1) * sum(runningCosts[i to j]) ≤ budget

To do this efficiently:
1. We use a sliding window from left to right and expand the window by increasing `right`.
2. To track the **maximum chargeTime** in the window efficiently, we maintain a **monotonic decreasing deque** (store indices).
   - The front of the deque always gives us the current max(chargeTime).
   - Before pushing a new index, pop all elements from the back with chargeTime ≤ current.
3. The **sum of runningCosts** is tracked using a variable `windowSum`.

Cost for a window [left, right] is:
    → max(chargeTime in window) + windowSize * windowSum

If cost exceeds budget, shrink the window from the left:
    → Remove expired `runningCosts[left]` and possibly pop deque front (if index was left)

4. Keep updating the maximum window size (`right - left + 1`) that satisfies the condition.

Time Complexity: O(n)
- Each index is pushed and popped from the deque at most once.

Space Complexity: O(n)
- At most all indices stored in deque in worst case.

*/

