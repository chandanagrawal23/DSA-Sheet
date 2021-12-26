class Solution {
public:
    int numberOfSubarrays(vector<int>& A, int K) {
     return atMostK(A, K) - atMostK(A, K - 1);
    }
    int atMostK(vector<int>& A, int K) {
        int i = 0, res = 0;
        int odd = 0;
        for (int j = 0; j < A.size(); ++j) {
            odd+=(A[j]%2);
            while(odd>K)
            {
                odd-=(A[i]%2);
                i++;
            }
            res += (j - i + 1);
        }
        return res;
    }
};


// k times  = at mostk times  - at most k-1 times
