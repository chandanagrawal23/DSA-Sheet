// Selection Sort
class Solution {
public:
    // Selection Sort - Unstable, O(n^2)
    // Select the minimum element and move it to the front
    void SelectionSort(vector<int>& a)
    {
        int n = a.size();
        for (int i = 0; i < n - 1; ++i)
        {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j)
            {
                if (a[j] < a[minIdx])
                    minIdx = j;
            }
            if (minIdx != i) // Avoid unnecessary swap
                swap(a[i], a[minIdx]);
        }
    }
};

/*
Approach:
- For each position, find the smallest element in the unsorted part
- Place it at the current position
- Optimization: skip swap if the min element is already in position

Time Complexity: O(n^2) for all cases
Space Complexity: O(1) (in-place)
*/
