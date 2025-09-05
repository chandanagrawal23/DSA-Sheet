// https://leetcode.com/problems/top-k-frequent-elements/

// ----------------- Approach 1 : Min Heap -----------------
class Solution
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        unordered_map<int, int> freq;
        for (int num : nums)
            freq[num]++;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

        for (auto& it : freq)
        {
            pq.push({it.second, it.first});
            if (pq.size() > k) 
                pq.pop(); // keep only k most frequent
        }

        vector<int> res;
        while (!pq.empty())
        {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};

/*
-------------------- APPROACH 1 (Min Heap) --------------------
1. Count frequency of each element using unordered_map.
2. Maintain a min-heap of size k (store {frequency, element}).
3. Whenever heap size > k, remove the smallest frequency element.
4. At the end, heap contains k most frequent elements.

✔ Efficient when k is small compared to n.
Time Complexity  : O(n log k) → each insert/pop in heap takes log k
Space Complexity : O(n + k) → freq map + heap
--------------------------------------------------------------
*/


// ----------------- Approach 2 : Max Heap -----------------
class Solution
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        unordered_map<int, int> freq;
        for (int num : nums)
            freq[num]++;

        priority_queue<pair<int,int>> pq; // max heap by default

        for (auto& it : freq)
            pq.push({it.second, it.first});

        vector<int> res;
        for (int i = 0; i < k; i++)
        {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};

/*
-------------------- APPROACH 2 (Max Heap) --------------------
1. Count frequency of each element.
2. Push all {frequency, element} into a max heap.
3. Pop top k elements → they are most frequent.

✔ Simple to implement but pushes all elements in heap.
Time Complexity  : O(n log n) → n insertions in heap
Space Complexity : O(n) → freq map + heap
--------------------------------------------------------------
*/


// ----------------- Approach 3 : Bucket Sort (IMPO)-----------------
class Solution
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        unordered_map<int, int> freq;
        for (int num : nums)
            freq[num]++;

        int n = nums.size();
        vector<vector<int>> buckets(n + 1); 
        for (auto& it : freq)
            buckets[it.second].push_back(it.first);

        vector<int> res;
        for (int i = n; i >= 1 && res.size() < k; i--)
        {
            for (int num : buckets[i])
            {
                res.push_back(num);
                if (res.size() == k) 
                    break;
            }
        }
        return res;
    }
};

/*
-------------------- APPROACH 3 (Bucket Sort) --------------------
1. Count frequency of each element.
2. Create buckets where index = frequency, 
   and store all numbers having that frequency.
   Example: buckets[3] → all numbers occurring 3 times.
3. Iterate from highest frequency downwards, 
   and collect elements until we have k.

✔ Most efficient when n is large and values are diverse.
Time Complexity  : O(n) → counting + bucket traversal
Space Complexity : O(n) → freq map + buckets
--------------------------------------------------------------
*/
