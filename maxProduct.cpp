//https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        priority_queue<int> pq;
        
        for(int &num : nums)
            pq.push(num - 1);
        
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        
        return a * b;
    }
};
