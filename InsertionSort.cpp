// Insertion Sort
class Solution {
public:
    // Insertion Sort - Stable, O(n^2) worst/average, O(n) best
    // Place each element in its correct position in sorted part
    void InsertionSort(vector<int>& a)
    {
        int n = a.size();
        for (int i = 1; i < n; ++i)
        {
            int key = a[i];
            int j = i - 1;
            while (j >= 0 && a[j] > key)
            {
                a[j + 1] = a[j];
                --j;
            }
            a[j + 1] = key;
        }
    }
};

/*
Approach:
- Traverse from left to right
- Move current element leftward into its correct position among sorted prefix
- Efficient for nearly sorted data

Time Complexity:
- Worst/Average: O(n^2)
- Best (already sorted): O(n)

Space Complexity: O(1) (in-place)
*/
