// using Max-Heap, read approach first
class Solution
{
public:
    int findMaxValueOfEquation(vector<vector<int>> &points, int k)
    {
        // Max heap: {yi - xi, xi}
        priority_queue<pair<int, int>> pq;
        int ans = INT_MIN;

        for (auto &p : points)
        {
            int xj = p[0], yj = p[1];

            // Remove points whose xi ( which is pq.top().second ) is out of range
            while (!pq.empty() && xj - pq.top().second > k)
            {
                pq.pop();
            }

            // If heap has valid i, compute value
            if (!pq.empty())
            {
                int maxVal = pq.top().first; // yi - xi
                ans = max(ans, maxVal + yj + xj); // (yi - xi) + yj + xj
            }

            // Push current (yj - xj, xj)
            pq.push({yj - xj, xj});
        }

        return ans;
    }
};

/*

Approach:
==========
We are given sorted 2D points (by x) and want to maximize the value:
    yi + yj + |xi - xj|
Given: xi < xj always, so |xi - xj| = xj - xi

Rewriting the expression:
    yi + yj + xj - xi
=   (yi - xi) + (yj + xj)

So, for every point j (moving left to right),
we want to find a past point i such that:
    xj - xi <= k    [distance constraint]
and maximize:
    (yi - xi)

To do this, we maintain a max-heap of past (yi - xi, xi),
and remove entries from heap if xj - xi > k.

Then, for valid heap top, we compute:
    maxVal = (yi - xi)
    Total value = maxVal + yj + xj
and update the answer.

Push the current point into the heap as (yj - xj, xj)
for future comparisons.

Time:  O(n log n)   [each point enters/leaves heap once]
Space: O(n)

*/ 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// using Monotonic DeQueue

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findMaxValueOfEquation(vector<vector<int>> &points, int k)
    {
        // Deque stores {yi - xi, xi}, maintaining decreasing order of (yi - xi)
        deque<pair<int, int>> dq;
        int ans = INT_MIN;

        for (auto &p : points)
        {
            int xj = p[0], yj = p[1];

            // Remove elements from front which are out of the allowed distance
            // Remove points whose xi ( which is dq.front().second )
            while (!dq.empty() && xj - dq.front().second > k)
            {
                dq.pop_front();
            }

            // If valid point exists in window, calculate maximum value
            if (!dq.empty())
            {
                int maxVal = dq.front().first; // max(yi - xi) so far
                ans = max(ans, maxVal + yj + xj); // (yi - xi) + yj + xj
            }

            // Maintain deque in decreasing order of (yj - xj)
            while (!dq.empty() && dq.back().first <= yj - xj)
            {
                dq.pop_back();
            }

            // Add current point
            dq.emplace_back(yj - xj, xj);
        }

        return ans;
    }
};
/*
Approach:
==========
We are given a list of 2D points sorted by xi, and we want to maximize:
    yi + yj + |xi - xj|

Since xi < xj always (due to sorting), |xi - xj| = xj - xi

So the equation becomes:
    yi + yj + (xj - xi)
=   (yi - xi) + (yj + xj)

This splits the equation into two parts:
1. (yi - xi): depends on a past point i
2. (yj + xj): depends on current point j

Observation:
------------
For each point j (traversed left to right), we need to find some point i before it such that:
    xj - xi ≤ k    ← (distance constraint)
and we want to "maximize (yi - xi)" among those valid points.

Efficient Solution:
--------------------
We use a "monotonic deque" to store pairs: (yi - xi, xi)

Deque properties:
- Maintains candidates for (yi - xi) in "decreasing order"
- Each element is a possible 'i' for future points 'j'

At each point j:
1. "Remove" front of deque if xi is too far (i.e., xj - xi > k)
2. "If deque is not empty", use its front to compute:
       maxValue = (yi - xi) + (yj + xj)
       Update answer accordingly
3. "Maintain monotonicity":
    - Remove from "back" any entry with (yi - xi) <= (yj - xj)
      → because current point is better or equal for future use
4. "Push current" (yj - xj, xj) to the back of deque

Why Monotonic Deque?
---------------------
- Front always has the maximum (yi - xi) in valid range
- Allows O(1) access to max
- Each point is inserted and removed at most once

Time Complexity: O(n) — each point is pushed/popped once
Space Complexity: O(n) — for the deque

*/
