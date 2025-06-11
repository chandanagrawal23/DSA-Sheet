// Bubble Sort
class Solution {
public:
    // Bubble Sort - Stable, O(n^2) worst/average, O(n) best when already sorted
    // Optimized by using a flag to detect early termination
    void BubbleSort(vector<int>& a)
    {
        int n = a.size();
        for (int i = 0; i < n - 1; ++i)
        {
            bool swapped = false;  // Flag to check if any swaps occurred in this pass
            for (int j = 0; j < n - i - 1; ++j)
            {
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // If no swaps, array is already sorted
        }
    }
};

/*
Approach:
- Traverse array multiple times
- Swap adjacent elements if they are in the wrong order
- Optimization: stop early if a pass completes with no swaps

Time Complexity:
- Worst/Average: O(n^2)
- Best (already sorted): O(n)

Space Complexity: O(1) (in-place)
*/
