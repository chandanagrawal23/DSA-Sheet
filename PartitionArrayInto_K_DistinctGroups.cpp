class Solution 
{
public:
    bool partitionArray(vector<int>& nums, int k) 
    {
        // If total number of elements is not divisible by k, partition is impossible
        if (nums.size() % k != 0)
        {
            return false;
        }

        unordered_map<int, int> freq;

        // Count the frequency of each number
        for (int x : nums)
        {
            freq[x]++;
        }

        int numGrps = nums.size() / k; // Maximum allowed occurrences per number

        // Check if any number occurs more than the allowed number of groups
        for (auto& p : freq) 
        {
            if (p.second > numGrps)
            {
                return false;
            }
        }

        // If all numbers satisfy the condition, partition is possible
        return true;
    }
};

/*
Approach (Detailed):

1. Frequency Counting:
   - Use an unordered_map to count how many times each number appears in the array.

2. Check Partition Feasibility:
   - The total number of elements must be divisible by k.
   - Let numGrps = total_elements / k.
   - Any number that appears more than numGrps times cannot fit into groups of size k 
     without repeating in a group. If such a number exists, return false.

3. Return Result:
   - If no number violates the maximum allowed occurrence, return true.

Time Complexity:
- O(n) for counting frequencies and checking the condition, where n = nums.size()

Space Complexity:
- O(n) for storing frequencies in the unordered_map
*/
