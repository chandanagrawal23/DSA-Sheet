class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        vector<int> myMap(10001,0);

        int left = 0;
        int right = 0;

        int res = 0;
        int tsum = 0;
        while (right < nums.size()) {
            int r = nums[right];
            tsum+=r;
            myMap[r]++;

            while (myMap[r] > 1) {
                int l = nums[left];
                myMap[l]--;
                left++;
                tsum-=l;
            }

            res = max(res, tsum);

            right++;
        }

        return res;
    }
};
