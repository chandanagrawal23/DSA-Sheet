/*class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        
        // create a priority queue (Max Heap) of pair of int
        // first of the pair is the element of the array
        // and second is the index
        priority_queue<pair<int,int>> p;
        // create a vector to store the result
        vector<int>res;
        // add all the elements in the first window to the PQ
        for(int i = 0; i < k; i++)
            p.push({arr[i],i});
        // add the max element of first window to the res vector
        res.push_back(p.top().first);
        // start iteration from the second window
        for(int i = k; i < arr.size(); i++)
        {
            // add the element into the PQ
            p.push({arr[i],i});
            // remove all the elments which are not in the current window
            // current window is from [i-k+1 , i]
            while(p.top().second <= i-k)
                p.pop();
            // add the max element in the PQ to the res
            res.push_back(p.top().first);
        }
        // return the result
        return res;
        
    }
};
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        map<int,int>mp;
        vector<int>ans;
        int i =0 , n = a.size();
        for(int j=0;j<n;j++)
        {
            mp[a[j]]++;
            while((j-i+1)==k)
            {
                ans.push_back(mp.rbegin()->first);
                mp[a[i]]--;
                if(mp[a[i]]==0)
                {
                    mp.erase(a[i]);
                }
                i++;
            }
        }
        return ans;
    }
};
