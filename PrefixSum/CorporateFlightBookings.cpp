#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n)
    {
        vector<int> seatsBooked(n, 0);

        for (auto &booking : bookings)
        {
            int start = booking[0] - 1;  // convert to 0-based index
            int end = booking[1] - 1;
            int seats = booking[2];

            seatsBooked[start] += seats;

            if (end + 1 < n)
            {
                seatsBooked[end + 1] -= seats;
            }
        }

        // Build prefix sum to get final seats booked per flight
        for (int i = 1; i < n; i++)
        {
            seatsBooked[i] += seatsBooked[i - 1];
        }

        return seatsBooked;
    }
};

/*
Approach:
- Use Difference Array + Prefix Sum to perform range seat additions efficiently.

For each booking [first, last, seats]:
  → Add 'seats' at index (first - 1)
  → Subtract 'seats' at index (last) to stop the addition beyond 'last'

Why subtract at (last + 1)?
- To stop adding 'seats' after the 'last' flight.
- When we compute prefix sum, the increase will apply from 'first' to 'last' only.

Example:
bookings = [ [1, 2, 10] ]
→ Add 10 at index 0
→ Subtract 10 at index 2

Final prefix sum will propagate:
[10, 10, 0, 0, ...] → after prefix sum = [10, 20, 20, ...]

Time Complexity: O(k + n)
- O(k) for applying k bookings
- O(n) for computing prefix sum

Space Complexity: O(n)
- One array of size n to hold results
*/
