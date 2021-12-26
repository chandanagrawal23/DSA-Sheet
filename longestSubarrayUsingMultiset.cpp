class Solution {
public:
      int longestSubarray(vector<int>& nums, int limit) 
    {
        multiset<int> s;
        int i=0 , j = 0 , ans = -1, n = nums.size();
        while(j<n)
        {
            s.insert(nums[j]);
            while(*s.rbegin() - *s.begin() > limit)
                s.erase(s.find(nums[i++]));     // s.erase(nums[i++]); this will remove all instance
            ans = max(ans , j-i+1);
            j++;
        }
        return ans;
    }
};
