
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double minAreaFreeRect(vector<vector<int>>& points)
    {
        int n = points.size();

        map<tuple<long long, long long, long long>,
        vector<pair<int, int>>> mp;

        double ans = DBL_MAX;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                long long dx = (long long)points[i][0] - points[j][0];
                long long dy = (long long)points[i][1] - points[j][1];

                long long len = dx * dx + dy * dy;

                long long midX = (long long)points[i][0] + points[j][0];
                long long midY = (long long)points[i][1] + points[j][1];

                mp[{midX, midY, len}].push_back({i, j});
            }
        }

        for (auto& entry : mp)
        {
            auto& diagonals = entry.second;

            for (int i = 0; i < (int)diagonals.size(); i++)
            {
                for (int j = i + 1; j < (int)diagonals.size(); j++)
                {
                    int p1 = diagonals[i].first;
                    int p2 = diagonals[j].first;
                    int p3 = diagonals[j].second;

                    long long dx1 = (long long)points[p1][0] - points[p2][0];
                    long long dy1 = (long long)points[p1][1] - points[p2][1];

                    long long dx2 = (long long)points[p1][0] - points[p3][0];
                    long long dy2 = (long long)points[p1][1] - points[p3][1];

                    double len1 = sqrt((double)dx1 * dx1 + (double)dy1 * dy1);
                    double len2 = sqrt((double)dx2 * dx2 + (double)dy2 * dy2);

                    double area = len1 * len2;

                    if (area > 0)
                    {
                        ans = min(ans, area);
                    }
                }
            }
        }

        return ans == DBL_MAX ? 0.0 : ans;
    }
};
/*
APPROACH
========

1. KEY OBSERVATION
------------------

The two diagonals of a rectangle have:
    1. The same midpoint.
    2. The same length.

Therefore, if two different point pairs have the same midpoint
and the same diagonal length, their four endpoints form a rectangle.


2. GROUP ALL POSSIBLE DIAGONALS
-------------------------------

Consider every pair of points (i, j) as a potential diagonal.

Calculate its squared length:

    len = (x1 - x2)^2 + (y1 - y2)^2

Calculate the doubled midpoint coordinates:

    midX = x1 + x2
    midY = y1 + y2

We do not divide the coordinates by 2 because we only need
to compare midpoints.

Use the following map key:

    {midX, midY, len}

Store every point pair with the same key in the same group.

Example:

    Rectangle:

    D(0,1) ---------------- C(2,1)
       |  \                /  |
       |    \            /    |
       |      \        /      |
       |        \    /        |
       |          O           |
       |        /    \        |
       |      /        \      |
       |    /            \    |
       |  /                \  |
    A(0,0) ---------------- B(2,0)


    Diagonal A-C:
        midX = 0 + 2 = 2
        midY = 0 + 1 = 1
        len  = (0-2)^2 + (0-1)^2 = 5

    Diagonal B-D:
        midX = 2 + 0 = 2
        midY = 0 + 1 = 1
        len  = (2-0)^2 + (0-1)^2 = 5

    Both diagonals have the same key:

        (2, 1, 5)

    Therefore, they belong to the same map group.


3. FIND RECTANGLES
------------------

Within each map group, consider every pair of diagonals.

Suppose:

    First diagonal:  (p1, p2)
    Second diagonal: (p3, p4)

Since their midpoints and lengths are equal, these two diagonals
form a rectangle.

All four points are required to identify the rectangle, but we
only need three points to calculate its area.


4. WHY ARE THREE POINTS ENOUGH?
-------------------------------

Consider this rectangle:

    D ---------------- C
    |                  |
    |                  |
    |                  |
    A ---------------- B

Suppose the diagonals are:

    First diagonal:  A-C
    Second diagonal: B-D

We select three points:

    p1 = A
    p3 = B
    p4 = D

These give us two adjacent sides:

    Side 1: A-B

        A ---------------- B

    Side 2: A-D

        D
        |
        |
        A

Notice that we do not need point C explicitly while calculating
the area.

Why does this work?

The two diagonals have the same midpoint and equal lengths.
These properties guarantee that the segments A-B and A-D are
perpendicular adjacent sides of the rectangle.

Therefore, we can calculate the area using just these three points.


5. CALCULATE THE AREA
---------------------

Calculate the first side:

    side1 = distance(p1, p3)

Calculate the second side:

    side2 = distance(p1, p4)

Using the Euclidean distance formula:

    distance(P, Q) = sqrt((Px - Qx)^2 + (Py - Qy)^2)

The area is:

    area = side1 * side2

For our example:

    AB = 2
    AD = 1

    Area = 2 * 1 = 2

Repeat this process for every pair of diagonals in every group
and keep the minimum positive area.


6. HANDLE THE CASE WHERE NO RECTANGLE EXISTS
--------------------------------------------

Initially:

    ans = DBL_MAX

Whenever a valid rectangle is found:

    ans = min(ans, area)

If ans remains DBL_MAX, no rectangle exists, so return 0.0.


COMPLEXITY ANALYSIS
===================

Let n be the number of points.

Time Complexity:
    Building the map: O(n^2 log n)
    Checking pairs of diagonals: O(n^4) in the worst case

    Overall: O(n^4)

Space Complexity:
    There are O(n^2) possible point pairs.

    Overall: O(n^2)
*/
