class NumArray 
{
public:
    vector<int> prefixSum;

    // Precompute prefix sum
    NumArray(vector<int>& num) 
    {
        prefixSum = num;
        for (int i = 1; i < prefixSum.size(); i++) 
        {
            prefixSum[i] += prefixSum[i - 1];
        }
    }

    // Return sum from left to right
    int sumRange(int left, int right) 
    {
        if (left == 0)
            return prefixSum[right];
        return prefixSum[right] - prefixSum[left - 1];
    }
};

/*
Approach:
- Build prefix sum array in constructor.
- sumRange(l, r) = prefix[r] - prefix[l-1] in O(1) time.

Time: O(n) for constructor, O(1) per query
Space: O(n)
*/

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
