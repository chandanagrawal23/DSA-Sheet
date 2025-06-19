class Solution {
public:
    int partitionArray(vector<int>& nums, int k) 
    {
        // Sort the array to group close elements together
        sort(nums.begin(), nums.end());

        int partitions = 1;        // Start with one partition
        int groupStart = 0;        // Index of the start of current group

        for (int i = 0; i < nums.size(); i++) 
        {
            // If the current number differs by more than k from the group start, start new group
            if (nums[i] - nums[groupStart] > k) 
            {
                partitions++;      // Increase partition count
                groupStart = i;    // Set new group start
            }
        }
        return partitions;
    }
};

/*
Approach:
1. Sort the array so that close numbers are together.
2. Traverse from left to right.
3. Start a new partition every time the difference between the current number 
   and the start of the current group exceeds 'k'.
4. Count how many such partitions are needed.
Time Complexity: O(n log n) due to sorting
Space Complexity: O(1)
*/
