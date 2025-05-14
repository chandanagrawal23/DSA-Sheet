class Solution {
public:
    vector<int> searchRange(vector<int>& a, int x) {
        return {firstPos(a, x), lastPos(a, x)};
    }

private:
    // Finds the first (leftmost) index of x in the array
    int firstPos(const vector<int>& arr, int x) {
        int low = 0, high = arr.size() - 1, res = -1;
        while (low <= high) 
        {
            int mid = low + (high - low) / 2;

            if (arr[mid] > x)
                high = mid - 1;
            else if (arr[mid] < x)
                low = mid + 1;
            else 
            {
                res = mid;       // Found x, but search left for first occurrence
                high = mid - 1;
            }
        }
        return res;
    }

    // Finds the last (rightmost) index of x in the array
    int lastPos(const vector<int>& arr, int x) {
        int low = 0, high = arr.size() - 1, res = -1;
        while (low <= high) 
        {
            int mid = low + (high - low) / 2;

            if (arr[mid] > x)
                high = mid - 1;
            else if (arr[mid] < x)
                low = mid + 1;
            else 
            {
                res = mid;       // Found x, but search right for last occurrence
                low = mid + 1;
            }
        }
        return res;
    }
};

/*
// using lower_bound and upper_bound

vector<int> searchRange(vector<int>& nums, int target) {
    int firstIndex = lower_bound(nums.begin(), nums.end(), target) - nums.begin();

    // Check if the target is not found
    if (firstIndex == nums.size() || nums[firstIndex] != target)
        return {-1, -1};

    int lastIndex = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;

    return {firstIndex, lastIndex};
}

/*
    📌 lower_bound(start, end, value)
    Returns an iterator pointing to the first element that is not less than (>=) the given value.
    
    If the value is present, it points to the first occurrence.
    
    If the value is not present, it points to the next greater element.
    
    If all elements are smaller, it returns end().
    
    📌 upper_bound(start, end, value)
    Returns an iterator pointing to the first element that is greater than (>) the given value.
    
    Always skips duplicates of the target value.


*/



*/
