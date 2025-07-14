class Solution
{
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>> &firstList, vector<vector<int>> &secondList)
    {
        vector<vector<int>> intersections;

        int i = 0, j = 0;

        while (i < firstList.size() && j < secondList.size())
        {
            int startA = firstList[i][0], endA = firstList[i][1];
            int startB = secondList[j][0], endB = secondList[j][1];

            // Find the intersection between current intervals
            int intersectionStart = max(startA, startB);
            int intersectionEnd = min(endA, endB);

            if (intersectionStart <= intersectionEnd)
            {
                intersections.push_back({intersectionStart, intersectionEnd});
            }

            // Move the pointer with the smaller end
            if (endA < endB)
            {
                i++;
            }
            else
            {
                j++;
            }
        }

        return intersections;
    }
};

/**
Approach:
We are given two lists of non-overlapping intervals, sorted by start time.
The goal is to find all overlapping intervals (intersections) between the two lists.

Steps:
1. Use two pointers `i` and `j` to iterate over both interval lists.
2. For each pair (firstList[i], secondList[j]):
   - Compute the maximum start and minimum end.
   - If they overlap (`start <= end`), add the intersection to the result.
3. Move the pointer whose interval ends first — this ensures no overlapping intervals are skipped.

Why it works:
- Since both input lists are sorted and disjoint, a two-pointer traversal guarantees all matches are checked efficiently.

Time Complexity:
- O(N + M), where N and M are the sizes of the two input lists.

Space Complexity:
- O(K), where K is the number of intersections added to the result.
*/
