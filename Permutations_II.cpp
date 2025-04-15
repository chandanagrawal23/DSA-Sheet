class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
	    vector<vector<int> > result;
      sort(num.begin(),num.end());
	    permuteRecursive(num, 0, result);
	    return result;
    }
    
    // permute num[begin..end]
    // invariant: num[0..begin-1] have been fixed/permuted
	void permuteRecursive(vector<int> num, int begin, vector<vector<int> > &result)	{
		if (begin == num.size()) {
		    // one permutation instance
		    result.push_back(num);
		    return;
		}
		
		for (int i = begin; i < num.size(); i++) {
            //set
            if((i!=begin) and (num[begin]==num[i])) continue;
		    swap(num[begin], num[i]);
            // recur
		    permuteRecursive(num, begin + 1, result);

		}
    }
};
