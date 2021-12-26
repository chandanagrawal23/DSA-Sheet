class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return atMostK(A, K) - atMostK(A, K - 1);
    }
    int atMostK(vector<int>& A, int K) {
        int left = 0, res = 0;
        unordered_map<int, int> count;
        for (int right = 0; right < A.size(); ++right) {
            count[A[right]]++;
            while(count.size()>K)
            {
                count[A[left]]--;
                if(count[A[left]]==0)
                    count.erase(A[left]);
                left++;
            }
            // res = max(res , right-left+1);
            res += (right-left + 1);
        }
        return res;
    }
    
    
};
