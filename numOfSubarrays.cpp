class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int cnt = 0;  // s for sum of sliding window, cnt for count
		int requiredSum = k * threshold; // t is the min sum for subarr of k len sliding window
        int currSum = 0;
        for(int i=0;i<k;i++)
            currSum += arr[i];
        if (currSum >=requiredSum) cnt++;
        for (int i = k; i < arr.size(); i++)
        {
            currSum += arr[i];  // accumulative sum adding head 
            currSum -= arr[i - k];  // accumulative sum substract tail
            if (currSum >=requiredSum)
                cnt++;  // found one
        }
        return cnt;
    }
};
