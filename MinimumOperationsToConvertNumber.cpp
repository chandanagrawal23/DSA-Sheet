//https://leetcode.com/problems/minimum-operations-to-convert-number/
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        vector<bool>visited(1001,false);
        int ans=0;
        queue<int>q;
        q.push(start);
        while(!q.empty()){
            int size=q.size();
            while(size--){
                int node=q.front();q.pop();
                if(node==goal)
                    return ans;
                if(node>1000 || node<0 || visited[node])
                    continue;
                visited[node]=true;
                for(int i=0;i<nums.size();i++){
                    int a=node+nums[i];
                    int b=node-nums[i];
                    int c=node^nums[i];
                    q.push(a);
                    q.push(b);
                    q.push(c);
                }
            }
            ans++;
        }
        return -1;
    }
};

/*
Just do simple BFS and maintain a visited array to keep track of numbers that we have seen already.

Here keypoint is numbers can be from 0 to 1000 so make visited array and once we have seen that number we don't have to include that number again.

*/
