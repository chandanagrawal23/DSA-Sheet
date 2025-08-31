#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findSmallest(vector<int>& arr) {
        if (arr.empty()) return -1;
        int minVal = arr[0];
        for (int num : arr)
            if (num < minVal)
                minVal = num;
        return minVal;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {10, 20, 3, 5, 1};
    vector<int> arr2 = {50, 40, 70, 100};

    cout << "Smallest in arr1: " << sol.findSmallest(arr1) << endl;
    cout << "Smallest in arr2: " << sol.findSmallest(arr2) << endl;

    return 0;
}

/*
Approach:
- Initialize min with first element.
- Traverse array and update min when a smaller element is found.

Time Complexity: O(n)
Space Complexity: O(1)
*/
