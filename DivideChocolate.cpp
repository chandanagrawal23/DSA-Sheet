class Solution 
{
public:
    // Helper to check if we can divide into (k + 1) people with at least 'minSweet' each
    bool canDivide(vector<int>& sweetness, int k, int minSweet) 
    {
        int people = 0, curr = 0;

        for (int s : sweetness) 
        {
            curr += s;

            if (curr >= minSweet) 
            {
                people++;
                curr = 0;
            }
        }

        return people >= k + 1;
    }

    int maximizeSweetness(vector<int>& sweetness, int k) 
    {
        // Minimum possible sweetness per person is at least the smallest chunk
        int left = *min_element(sweetness.begin(), sweetness.end());

        // Maximum possible sweetness per person is total divided among (k+1)
        int right = accumulate(sweetness.begin(), sweetness.end(), 0);
        int ans = 0;

        while (left <= right) 
        {
            int mid = left + (right - left) / 2;

            if (canDivide(sweetness, k, mid)) 
            {
                ans = mid;        // Valid division, try for more
                left = mid + 1;
            } 
            else 
            {
                right = mid - 1;  // Too much sweetness, reduce
            }
        }

        return ans;
    }
};

/*
Approach: Binary Search on Answer

We are given an array of sweetness levels and asked to divide it into k + 1 contiguous parts (people), such that the minimum sweetness among all people is maximized.

Goal:
Maximize the minimum total sweetness among (k + 1) people.

Key Insight:
If we fix a value 'minSweet', we can check if it's possible to divide the array into (k + 1) or more contiguous parts such that each part has at least minSweet total sweetness.

Strategy:
- We apply binary search on the possible sweetness range [1, total_sum].
- At each step, check if we can partition the array into ≥ k + 1 parts with each part ≥ mid.
- If yes, it's a valid candidate. Try to increase sweetness.
- If not, decrease mid.

Helper Function `canDivide(sweetness, k, minSweet)`:
- Traverse the array while maintaining a current sum.
- Each time the sum reaches or exceeds minSweet, count it as one partition.
- Reset sum and repeat.
- At the end, check if the number of such partitions ≥ (k + 1)

Time Complexity:
- O(N log S), where N = size of array, S = total sum of sweetness
  - O(log S) binary search steps
  - O(N) check for each step

Space Complexity:
- O(1), constant extra space
*/
