//https://leetcode.com/problems/kth-largest-element-in-an-array/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //Kth larget - use max heap , TC - KlogN + N  , SC - O(n) , pop k-1 times
//      priority_queue<int> pq (nums.begin(),nums.end());
//         k--;
//         while(k--)
//         {
//             pq.pop();
//         }
        
//     return pq.top();
        
        //use min heap , TC - Nlogk  , SC - O(K) , pop all elements
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};
