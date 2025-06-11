// Recursive Merge Sort
class Solution {
public:
    // Merge Sort - Stable, O(n log n), extra O(n) space
    // Divide array, sort halves recursively, then merge
    void MergeSort(vector<int>& a)
    {
        vector<int> temp(a.size());
        mergeSortHelper(a, temp, 0, a.size() - 1);
    }

private:
    void mergeSortHelper(vector<int>& a, vector<int>& temp, int left, int right)
    {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortHelper(a, temp, left, mid);
        mergeSortHelper(a, temp, mid + 1, right);
        merge(a, temp, left, mid, right);
    }

    void merge(vector<int>& a, vector<int>& temp, int left, int mid, int right)
    {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right)
        {
            if (a[i] <= a[j]) temp[k++] = a[i++];
            else temp[k++] = a[j++];
        }
        while (i <= mid) temp[k++] = a[i++];
        while (j <= right) temp[k++] = a[j++];
        for (int idx = left; idx <= right; ++idx)
            a[idx] = temp[idx];
    }
};

/*
Approach:
- Recursively divide the array into halves
- Sort each half
- Merge the two sorted halves

Time Complexity: O(n log n)
Space Complexity: O(n) for auxiliary array
*/


// ===================================================================================================================================


// Iterative Merge Sort
class Solution {
public:
    // Iterative Merge Sort - Bottom-up approach
    // Avoids recursion stack, still O(n log n) time and O(n) space
    void IterativeMergeSort(vector<int>& a)
    {
        int n = a.size();
        vector<int> temp(n);

        for (int size = 1; size < n; size *= 2)
        {
            for (int left = 0; left < n - size; left += 2 * size)
            {
                int mid = left + size - 1;
                int right = min(left + 2 * size - 1, n - 1);
                merge(a, temp, left, mid, right);
            }
        }
    }

private:
    void merge(vector<int>& a, vector<int>& temp, int left, int mid, int right)
    {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right)
        {
            if (a[i] <= a[j]) temp[k++] = a[i++];
            else temp[k++] = a[j++];
        }
        while (i <= mid) temp[k++] = a[i++];
        while (j <= right) temp[k++] = a[j++];
        for (int idx = left; idx <= right; ++idx)
            a[idx] = temp[idx];
    }
};

/*
Approach:
- Start by merging subarrays of size 1, then 2, 4, 8, etc.
- This is the bottom-up implementation of merge sort
- Merges done iteratively using loops instead of recursion

Time Complexity: O(n log n)
Space Complexity: O(n) for auxiliary array
*/

