//https://leetcode.com/problems/last-stone-weight/
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int>pq;
        for(auto xt : stones)
                pq.push(xt);
         while(pq.size()!=1){
          int x = pq.top();
             pq.pop();
           int y = pq.top();
             pq.pop();
           pq.push(x-y);
         }
        return pq.top();
        
    }
};
