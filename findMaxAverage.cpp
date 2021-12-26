class Solution {
public:
    double findMaxAverage(vector<int>& a, int k) {
        double ans = -1000000000.0;
        double sum=0;
        for(int i=0;i<k;i++)
            sum+=a[i];
        ans = max(ans,sum/(k*1.0));
        for(int i=k;i<a.size();i++)
        {
            sum += a[i];
            sum -= a[i-k];
            ans = max(ans,sum/(k*1.0));
        }
        return ans;
    }
};

        // int p = 0;
        // int n = a.size();
        // for(int i=0;i<n;i++)
        // {
        //     sum+=a[i];
        //     if((i-p+1)==k)
        //     {
        //         ans = max(ans,sum/(k*1.0));
        //         sum-=a[p];
        //         p++;
        //     }
        // }

// 1 2 3 4 5
