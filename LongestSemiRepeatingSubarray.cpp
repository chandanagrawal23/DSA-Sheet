class Solution
{
public:
    int longestSubarray(vector<int>& nums, int k)
    {
        int n = nums.size();

        // unordered_map<int, int> freq;
        vector<int>freq(1e5+1,0);
        int left = 0;
        int repeating = 0;
        int ans = 0;

        for (int right = 0; right < n; right++)
        {
            freq[nums[right]]++;

            if (freq[nums[right]] == 2) // 1 se jyada yaani first baar 2 hote hote hi repeating me count kro
            {
                repeating++;
            }

            while (repeating > k)
            {
                freq[nums[left]]--;

                if (freq[nums[left]] == 1) // 2 se kam yaani pehle baar ek hote hi repeating me hta do
                {
                    repeating--;
                }

                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
