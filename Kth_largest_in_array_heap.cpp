// ──────────────── MAX-HEAP SOLUTION ────────────────
class SolutionMaxHeap
{
public:
    // kth-largest using a max-heap of all N elements
    int findKthLargest(vector<int>& nums, int k)
    {
        priority_queue<int> pq(nums.begin(), nums.end());   // O(N) build
        while (--k) 
            pq.pop();                                       // pop k-1 times
        return pq.top();                                    // kth largest
    }
};


/*  Approach (max-heap):
    • Build a max-heap from all N values (linear-time heapify).  
    • Pop the largest element k-1 times; the next top is the kth largest.

       Time  : O(N + k log N)   (≈ O(N log N) worst when k≈N)
       Space : O(N)             (heap stores all N elements)                  
*/












// ──────────────── MIN-HEAP SOLUTION ────────────────
class SolutionMinHeap
{
public:
    // kth-largest using a size-k min-heap
    int findKthLargest(vector<int>& nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> pq;  // min-heap
        for (int x : nums)
        {
            pq.push(x);             // log k
            if (pq.size() > k)      // keep only k largest
                pq.pop();
        }
        return pq.top();            // kth largest
    }
};

/*  Approach (min-heap):
    • Maintain a min-heap of size k holding the k largest seen so far.  
    • Push each number; if size exceeds k, pop the smallest.  
    • Heap top is the kth largest after scanning all N numbers.

       Time  : O(N log k)          (fast when k ≪ N)  
       Space : O(k)                (heap holds k elements)                        
*/
