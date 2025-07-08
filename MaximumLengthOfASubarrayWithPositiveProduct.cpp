class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int negCount = 0, firstPosIndex = -1, firstNegIndex = -1, result = 0;

        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0)
                firstPosIndex = i, negCount = 0;
            else 
            {
                if(nums[i] < 0) 
                {
                    negCount++;

                    if(negCount == 1)
                        firstNegIndex = i;
                }

                if(negCount % 2 == 0)
                    result = max(result, i - firstPosIndex);
                else
                    result = max(result, i - firstNegIndex);
            }
        }

        return result;
    }
};

/*

we maintain 2 variables firstPosIndex which will store the index before the first positive number
 in the subarray and firstNegIndex which stores the first negative number in the subarray.

we also store the number of negatives in the subarray, if this is even (ie positive product) 
then we compute the length of the subarray from firstPosIndex, 
if it is negative (ie. we need to knock out the first negative to make it valid) 
then we compute from firstNegIndex


*/
