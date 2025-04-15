class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double lowY = 1e18, highY = -1e18;
        for (const auto& sq : squares)
         {  
            double x = sq[0], y = sq[1], len = sq[2];  // Explicit element extraction

            lowY = min(lowY, static_cast<double>(y));

            highY = max(highY, static_cast<double>(y + len));
        }

        double eps = 1e-6, ansY = lowY;
        while (highY - lowY > eps)
         {
            double midY = (lowY + highY) / 2;
            double upper = 0, lower = 0;

            for (const auto& sq : squares) 
            {
                double x = sq[0], y = sq[1], len = sq[2];  // Explicit element extraction

                double topY = y + len;

                if (topY <= midY)
                {
                    lower += len * len;
                } 
                else if (y >= midY)
                {
                    upper += len * len;
                }
                else
                {
                    double below = midY - y;
                    double above = topY - midY;
                    lower += below * len;
                    upper += above * len;
                }
            }

            if (upper > lower)
            {
                lowY = midY;
                ansY = midY;
            }
            else
            {
                highY = midY;
                // ansY = midY;  // Store the current best mid value
            }
        }
        return ansY;
    }
};


// if we have to divide on X 

/*

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double lowX = 1e18, highX = -1e18;
        for (const auto& sq : squares) {  
            double x = sq[0], y = sq[1], len = sq[2];

            lowX = min(lowX, static_cast<double>(x));
            highX = max(highX, static_cast<double>(x + len));
        }

        double eps = 1e-5, ansX = lowX;
        while (highX - lowX > eps) {
            double midX = (lowX + highX) / 2;
            double left = 0, right = 0;

            for (const auto& sq : squares) {
                double x = sq[0], y = sq[1], len = sq[2];
                double topX = x + len;

                if (topX <= midX) {
                    left += len * len;  // Square is fully on the left
                } 
                else if (x >= midX) {
                    right += len * len;  // Square is fully on the right
                }
                else {
                    double leftPart = midX - x;
                    double rightPart = topX - midX;
                    left += leftPart * len;   // Left portion of the square
                    right += rightPart * len; // Right portion of the square
                }
            }

            if (right > left) {
                lowX = midX;
            } else {
                highX = midX;
                ansX = midX;  // Store the current best mid value
            }
        }
        return ansX;
    }
};

// Driver Code
int main() {
    Solution sol;
    vector<vector<int>> squares = { {0, 2, 4}, {1, 5, 3}, {3, 1, 2} };
    cout << sol.separateSquares(squares) << endl;
    return 0;
}


*/
