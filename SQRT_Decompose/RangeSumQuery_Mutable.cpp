// ------------------ Approach 1 : Brute Force ------------------
class NumArray1 
{
public:
    vector<int> arr;

    NumArray1(vector<int>& nums) 
    {
        arr = nums;   // store input array
    }
    
    void update(int index, int val) 
    {
        arr[index] = val;   // directly update element
    }
    
    int sumRange(int left, int right) 
    {
        int sum = 0;
        // scan from left → right and accumulate
        for (int i = left; i <= right; i++)
            sum += arr[i];
        return sum;
    }
};

/*
-------------------- APPROACH 1 (Brute Force) --------------------
- Keep nums in a simple array.
- update() → O(1) (just assign).
- sumRange() → O(n) in worst case (scan subarray).

✔ Very easy to implement.
✘ Too slow when queries are many.

Time Complexity  : update O(1), sumRange O(n)
Space Complexity : O(n)
---------------------------------------------------
*/


// ------------------ Approach 2 : SQRT Decomposition ------------------
class NumArray2 
{
public:
    struct Bucket 
    {
        int sum;            // stores total sum of bucket
        vector<int> val;    // stores elements of bucket
    };

    int bucketNum;          // total buckets
    int bucketSize;         // size of each bucket
    vector<Bucket> Bs;      // array of buckets

    NumArray2(vector<int> &nums) 
    {
        int size = nums.size();
        bucketNum = (int)sqrt(2 * size);  // approx bucket count
        bucketSize = bucketNum / 2;       // approx bucket size
        while(bucketSize * bucketNum < size) ++bucketSize;  // adjust size
        
        Bs.resize(bucketNum);
        for(int i = 0, k = 0; i < bucketNum; ++i) 
        {
            int temp = 0;
            Bs[i].val.resize(bucketSize);
            for(int j = 0; j < bucketSize && k < size; ++j, ++k) 
            {
                temp += nums[k];         // update bucket sum
                Bs[i].val[j] = nums[k];  // store element in bucket
            }
            Bs[i].sum = temp;            // finalize sum for this bucket
        }
    }

    void update(int i, int val) 
    {
        int x = i / bucketSize;   // bucket index
        int y = i % bucketSize;   // position inside bucket
        Bs[x].sum += (val - Bs[x].val[y]); // adjust bucket sum
        Bs[x].val[y] = val;       // update value
    }

    int sumRange(int i, int j) 
    {
        int x1 = i / bucketSize, y1 = i % bucketSize; // start bucket
        int x2 = j / bucketSize, y2 = j % bucketSize; // end bucket
        int sum = 0;

        // case 1: both indices in same bucket
        if(x1 == x2) 
        {
            for(int a = y1; a <= y2; ++a)
                sum += Bs[x1].val[a];
            return sum;
        }

        // case 2: span multiple buckets
        for(int a = y1; a < bucketSize; ++a) 
                sum += Bs[x1].val[a];         // from left partial
        for(int a = x1 + 1; a < x2; ++a) 
                sum += Bs[a].sum;             // full middle buckets
        for(int b = 0; b <= y2; ++b) 
                sum += Bs[x2].val[b];         // from right partial

        return sum;
    }
};

/*
-------------------- APPROACH 2 (SQRT Decomposition) --------------------
- Split array into √n buckets.
- Each bucket stores sum + values.
- update(): update value and adjust bucket sum (O(1)).
- sumRange(): 
   - If range inside 1 bucket → scan directly.
   - Else → add from partial left bucket + all full buckets in middle + partial right bucket.

✔ Much faster than brute force.
Time Complexity  : update O(1), sumRange O(√n)
Space Complexity : O(n)
---------------------------------------------------
*/
