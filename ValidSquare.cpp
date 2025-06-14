class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // Instead of computing actual distances (root((x2-x1)^2 + (y2-y1)^2)) , I am calcualting it's square so that there will be no floating point error 
        vector<int> dists = 
        {
            distSq(p1, p2),
            distSq(p1, p3),
            distSq(p1, p4),
            distSq(p2, p3),
            distSq(p2, p4),
            distSq(p3, p4)
        };

        unordered_map<int, int> freq;
        for (int d : dists) 
        {
            if (d == 0) 
                return false; // overlapping or identical points can't form a square
            freq[d]++;
        }

        // A valid square will only have 2 unique distances:
        // - 4 equal side lengths (shorter distance)
        // - 2 equal diagonal lengths (longer distance)
        if (freq.size() != 2) return false;

        bool has4 = false, has2 = false;
        for (auto& [val, count] : freq) 
        {
            if (count == 4) 
                has4 = true; // 4 sides
            else if (count == 2) 
                has2 = true; // 2 diagonals
        }

        return has4 && has2;
    }

    int distSq(vector<int>& a, vector<int>& b) {
        int dx = a[0] - b[0];
        int dy = a[1] - b[1];
        return dx * dx + dy * dy;
    }
};

/*
Approach:

- To form a valid square using 4 points:
    1. All 4 sides must be of equal length.
    2. Both diagonals must be of equal length and longer than the sides.
    3. No two points should overlap.

- For 4 points, there are 6 unique pairwise distances:
    - 4 of them should be equal (sides)
    - 2 of them should be equal and longer (diagonals)

- Instead of calculating real distances (which involve square roots), we compute
  **squared distances** to avoid floating point inaccuracies.

- We count the frequency of each squared distance:
    - There should be exactly 2 distinct squared distances.
    - One should occur 4 times (sides), and the other 2 times (diagonals).

- If these conditions hold, the points form a valid square.

Time Complexity: O(1) — fixed number of operations for 4 points.  
Space Complexity: O(1) — we only store frequencies for up to 6 distances.
*/
