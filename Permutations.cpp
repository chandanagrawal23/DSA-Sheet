class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
	    vector<vector<int> > result;
	    permuteRecursive(num, 0, result);
	    return result;
    }
    
    // permute num[begin..end]
    // invariant: num[0..begin-1] have been fixed/permuted
	void permuteRecursive(vector<int> &num, int begin, vector<vector<int> > &result)	{
		if (begin == num.size()) {
		    // one permutation instance
		    result.push_back(num);
		    return;
		}
		
		for (int i = begin; i < num.size(); i++) {
            //set
		    swap(num[begin], num[i]);
            
            // recur
		    permuteRecursive(num, begin + 1, result);
		    
            // reset
		    swap(num[begin], num[i]);
		}
    }
};



/*
manual next_permutation too -

bool manualNextPermutation(vector<int>& nums)
{
    int n = nums.size();

    // Step 1: Find the first index 'i' such that nums[i] < nums[i + 1] from right to left
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }

    // If no such index is found, the permutation is the last one
    if (i < 0)
    {
        reverse(nums.begin(), nums.end());
        return false;
    }

    // Step 2: Find the first index 'j' from the end such that nums[j] > nums[i]
    int j = n - 1;
    while (j > i && nums[j] <= nums[i])
    {
        j--;
    }

    // Step 3: Swap nums[i] and nums[j]
    swap(nums[i], nums[j]);

    // Step 4: Reverse the subarray from i + 1 to the end
    reverse(nums.begin() + i + 1, nums.end());

    return true;
}
int main()
{
    vector<int> nums = {1, 2, 3};

    do {
        for (int num : nums)
            cout << num << " ";
        cout << '\n';
    } while (manualNextPermutation(nums));

    return 0;
}

*/
