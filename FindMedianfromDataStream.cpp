//https://leetcode.com/problems/find-median-from-data-stream/
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int> lo;                              // max heap
    priority_queue<int, vector<int>, greater<int>> hi;   // min heap
    
    MedianFinder() {
        ios_base::sync_with_stdio(false);    
        cin.tie(NULL);
    }
    
    void addNum(int num) {
        lo.push(num);  // add
        
        hi.push(lo.top()); // balance
        lo.pop();
        
        // balance size too
        if(hi.size()>lo.size())
        {
            lo.push(hi.top());
            hi.pop();
        }
    }
    
    double findMedian() {
        if(lo.size()>hi.size()) // means odd element
            return lo.top();
        else
            return((lo.top()+hi.top())/2.0);
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
