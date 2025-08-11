#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int eatenApples(vector<int> &apples, vector<int> &days)
    {
        int n = apples.size();
        // {expiryDay, count} min heap, early expiry day first
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; 
        int totalEaten = 0;
        int currentDay = 0;

        // Process each day during apple growth period
        for (; currentDay < n; currentDay++)
        {
            // Add today's apples with expiry day
            if (apples[currentDay] > 0)
                pq.push({currentDay + days[currentDay], apples[currentDay]});

            // Remove rotten apples (expiry <= currentDay)
            while (!pq.empty() && pq.top().first <= currentDay)
                pq.pop();

            // Eat one apple from the earliest expiring batch
            if (!pq.empty())
            {
                auto [expiryDay, count] = pq.top();
                pq.pop();
                totalEaten++;
                if (count > 1)
                    pq.push({expiryDay, count - 1});
            }
        }

        // After growth period ends, keep eating remaining apples in heap
        while (!pq.empty())
        {
            auto [expiryDay, count] = pq.top();
            pq.pop();

            // Can eat apples only before they expire
            if (expiryDay > currentDay)
            {
                int eatCount = min(count, expiryDay - currentDay);
                totalEaten += eatCount;
                currentDay += eatCount;
            }
        }

        return totalEaten;
    }
};

/*
Approach:
---------
1. Use a "min-heap" (priority_queue with greater<>) to always pick the apple batch 
   with the earliest expiry day.
   Each entry is {expiryDay, appleCount}.

2. For each day in the growth period:
   - Add today's apples to the heap with expiry day = currentDay + days[i].
   - Remove all batches that have expired (expiryDay <= currentDay).
   - Eat 1 apple from the earliest expiry batch (reduce count, push back if any remain).

3. After growth period ends:
   - Keep eating from the heap until it's empty.
   - For each batch, eat as many as possible before expiry.

Time Complexity:
----------------
O(NlogN)

Space Complexity:
-----------------
- Heap stores at most O(N+N) batches at a time.
- Overall: O(N).

*/
