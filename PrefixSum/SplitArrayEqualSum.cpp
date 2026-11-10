```cpp
class Solution
{
public:
    bool splitArray(vector<int>& nums)
    {
        int n = nums.size();

        vector<long long> pref(n);
        pref[0] = nums[0];

        for (int i = 1; i < n; i++)
            pref[i] = pref[i - 1] + nums[i];

        for (int j = 3; j < n - 3; j++)
        {
            unordered_set<long long> st;

            // Store valid left-side sums
            for (int i = 1; i < j - 1; i++)
            {
                long long s1 = pref[i - 1];      //sum from 0 to i-1
                long long s2 = pref[j - 1] - pref[i]; // sum from i+1 to j-1 which is pref[j-1] - pref[i+1-1] 

                if (s1 == s2)
                    st.insert(s1);
            }

            // Check matching right-side sums
            for (int k = j + 2; k < n - 1; k++)
            {
                long long s3 = pref[k - 1] - pref[j]; // sum from j+1 to k-1 => pref[k-1] - pref[j+1-1] 
                long long s4 = pref[n - 1] - pref[k]; // sum from k+1 to end = pref[n-1] - pref[k+1-1]

                if (s3 == s4 && st.count(s3))
                    return true;
            }
        }

        return false;
    }
};
```
