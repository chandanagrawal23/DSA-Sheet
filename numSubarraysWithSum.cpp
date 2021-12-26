class Solution {
public:
    
    // int subarraySum(vector<int>& a, int k) {
    //     unordered_map<int,int>mp;
    //     int cnt=0 , pre=0;
    //     for(int i=0;i<a.size();i++)
    //     {
    //         pre+=a[i];
    //         if(pre==k)
    //             cnt++;
    //         if(mp.find(pre-k)!=mp.end())
    //             cnt+=(mp[pre-k]);
    //         mp[pre]++;
    //     }
    //     return cnt;
    // }
     int numSubarraysWithSum(vector<int>& A, int S) {
         // return subarraySum(A,S);
        return atMost(A, S) - atMost(A, S - 1);
    }
    
    // exact chahiye , yani atmost (S) - at most (S-1)
    //how many subarrays whose sum is at most S
    int atMost(vector<int>& A, int S) {
        if (S < 0) return 0;
        int tot = 0;
        int res = 0, i = 0, n = A.size();
        for (int j = 0; j < n; j++) {
            tot += A[j];
            while (tot > S)
                tot -= A[i++];
            res += (j - i + 1);
        }
        return res;
    }
    
    /*
    int numSubarraysWithSum(vector<int>& a, int goal) {
        int left = 0 , right = 0 ;
        int n = a.size();
        int cnt = 0 , sum=0;
        while(right<n)
        {
            sum+=a[right];
            while(left<right and sum<goal)
            {
                sum-=a[left++];
            }
            if(sum==goal)
                cnt++;
            for (int i = left; sum == goal && i < right && a[i] == 0; i++)
                cnt++;
            right++;
        }
        return cnt;
    }
    */
};
