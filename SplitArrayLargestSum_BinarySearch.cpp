class Solution 
{
public:

    // Calculates how many minimum partitions are needed 
    // such that no partition has sum > maxSumAllowed
    int minPartitionRequired(vector<int>& a, int maxSumAllowed)
    {
        int currSum = 0;
        int partitions = 0;

        for (int i = 0; i < a.size(); i++)
        {
            if (currSum + a[i] <= maxSumAllowed)
            {
                currSum += a[i];
            }
            else
            {
                partitions++;
                currSum = a[i];
            }
        }

        return partitions + 1;  // final partition
    }

    // Calculates total sum of the array
    int sum(vector<int>& a)
    {
        int total = 0;
        for (int val : a)
        {
            total += val;
        }
        return total;
    }

    // Finds minimum possible largest partition sum 
    // when array is split into k or fewer subarrays
    int splitArray(vector<int>& a, int k)
    {
        int left = *max_element(a.begin(), a.end());  // minimum max sum possible
        int right = sum(a);                           // maximum max sum possible
        int ans = 0;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (minPartitionRequired(a, mid) <= k)
            {
                ans = mid;
                right = mid - 1;  // try to minimize
            }
            else
            {
                left = mid + 1;
            }
        }

        return ans;
    }
};

/*
Approach:
---------
- Use binary search on the answer (maximum subarray sum).
- For each mid value, check how many partitions are needed using minPartitionRequired().
- If partitions needed ≤ k, we try smaller values.
- Else, we increase mid.

Time Complexity:  O(n * log(sum of array))
Space Complexity: O(1)
*/
