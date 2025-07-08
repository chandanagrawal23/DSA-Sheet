/////////////////////// APPROACH 1: Prefix Sum + HashMap //////////////////////////

class Solution
{
public:
    int numSubarraysWithSum(vector<int>& nums, int goal)
    {
        unordered_map<int, int> mp;
        int prefixSum = 0, count = 0;

        for (int i = 0; i < nums.size(); ++i)
        {
            prefixSum += nums[i];

            if (prefixSum == goal)
                count++;

            if (mp.find(prefixSum - goal) != mp.end())
                count += mp[prefixSum - goal];

            mp[prefixSum]++;
        }

        return count;
    }
};

/*
Approach:
- Maintain running prefix sum.
- If (prefixSum - goal) has occurred before, it means there's a subarray ending here with sum equal to goal.
- Add the frequency of (prefixSum - goal) to result.
Time: O(n)
Space: O(n)
*/


/////////////////////// APPROACH 2: AtMost(goal) - AtMost(goal - 1) //////////////////////////

class Solution
{
public:
    int numSubarraysWithSum(vector<int>& nums, int goal)
    {
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }

    int atMost(vector<int>& nums, int goal)
    {
        if (goal < 0) return 0;

        int left = 0, right = 0, sum = 0, count = 0;

        for (; right < nums.size(); ++right)
        {
            sum += nums[right];

            while (sum > goal)
                sum -= nums[left++];

            count += (right - left + 1);
        }

        return count;
    }
};

/*
Approach:
- Count number of subarrays with sum <= goal and subtract those with sum <= goal-1.
- This gives number of subarrays with exact sum == goal.
- Works only when elements are 0 or 1.
Time: O(n)
Space: O(1)
*/


/////////////////////// APPROACH 3: Sliding Window + Leading Zeros Trick //////////////////////////

class Solution
{
public:
    int numSubarraysWithSum(vector<int>& nums, int goal)
    {
        int left = 0, right = 0, sum = 0, count = 0;
        int zeroPrefix = 0;

        while (right < nums.size())
        {
            sum += nums[right];

            // Shrink window if sum > goal or leading zero
            while (left < right && (sum > goal || nums[left] == 0))
            {
                if (nums[left] == 0)
                    zeroPrefix++;
                else
                    zeroPrefix = 0;

                sum -= nums[left++];
            }

            if (sum == goal)
                count += zeroPrefix + 1;

            right++;
        }

        return count;
    }
};

/*
Approach:
- Binary array only (0s and 1s).
- Expand window, and on finding sum == goal, count number of leading zeros to capture all valid subarrays.
- More optimal than a naive sliding window that checks each subarray.
Time: O(n)
Space: O(1)
*/
