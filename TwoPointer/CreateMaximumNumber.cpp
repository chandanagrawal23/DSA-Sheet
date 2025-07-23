class Solution 
{
public:

    // Extract max subsequence of length k from given array
    // Arr = [9,1,2,5,8,3] , K = 5 , means we have to drop 1 element
    // the max number we can form of length K(=5) , is 9 2 5 8 3
    vector<int> getMaxSubsequence(vector<int>& nums, int k) 
    {
        int drop = nums.size() - k;
        vector<int> stack;

        for (int num : nums) 
        {
            while (!stack.empty() && drop > 0 && stack.back() < num) 
            {
                stack.pop_back();
                drop--;
            }
            stack.push_back(num);
        }

        stack.resize(k); // keep only k elements
        return stack;
    }

    // Custom comparator: returns true if nums1[i..] < nums2[j..]
    bool greater(const vector<int>& nums1, int i, const vector<int>& nums2, int j) 
    {
        int m = nums1.size(), n = nums2.size();
        while (i < m && j < n && nums1[i] == nums2[j]) 
        {
            i++;
            j++;
        }
        return j < n && (i == m || nums1[i] < nums2[j]);
    }

    // Merge two subsequences to form the largest number
    vector<int> merge(vector<int>& a, vector<int>& b) 
    {
        vector<int> merged;
        int i = 0, j = 0;

        while (i < a.size() || j < b.size()) 
        {
            if (greater(a, i, b, j)) 
                merged.push_back(b[j++]);
            else 
                merged.push_back(a[i++]);
        }

        return merged;
    }

    // Try all splits and get the maximum number
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        vector<int> result;

        for (int i = 0; i <= k; ++i) 
        {
            if (i <= nums1.size() && (k - i) <= nums2.size()) 
            {
                vector<int> seq1 = getMaxSubsequence(nums1, i);
                vector<int> seq2 = getMaxSubsequence(nums2, k - i);

                vector<int> candidate = merge(seq1, seq2);
                result = max(result, candidate); // keep max lex result
            }
        }

        return result;
    }
};

/*
Problem:
Given two arrays of digits (nums1 and nums2), return the lexicographically largest number of length `k` that can be formed by picking digits from both arrays (relative order within each array must be preserved).

Strategy:
Try all combinations of choosing i digits from nums1 and (k - i) from nums2, and merge them optimally.

Step-by-step:
1 Loop from i = 0 to k:
    - Extract best subsequence of length i from nums1 (greedy using stack)
    - Extract best subsequence of length k-i from nums2
    - Merge the two to form the largest possible number

2 During merge:
    - Always pick the "greater" digit from the two sequences.
    - If equal digits, compare remaining parts to break tie.

3 Keep updating the result if the merged candidate is lexicographically greater.

Time Complexity:
- getMaxSubsequence: O(n)
- merge: O(k)
- Total: O(k * (m + n + k)) → acceptable for m, n ≤ 500

Space Complexity: O(k)

This is the classic greedy + simulation combo.
*/
