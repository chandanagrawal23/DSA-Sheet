class Solution {
public:
vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
    
    int n = s.size();

    vector<int> nextCandle(n, n);
    vector<int> prevCandle(n, -1);

    // Build prevCandle and prefixSum
    for (int i = 0; i < n; i++)
    {
        // if it is plate do nothing 
        if (s[i] == '*')
        {
            if (i == 0)
                prevCandle[i] = -1;
            else
                prevCandle[i] = prevCandle[i - 1];
        }
        // // if it is plate 
        else
        {
            prevCandle[i] = i;
        }
    }

    // Build nextCandle
    for (int i = n - 1; i >= 0; i--)
    {
        // if it is plate do nothing
        if (s[i] == '*')
        {
            if (i == n - 1)
                nextCandle[i] = n;
            else
                nextCandle[i] = nextCandle[i + 1];
        }
        else
        {
            nextCandle[i] = i;
        }
    }

    vector<int> prefixSum(n, 0);
    if(s[0] == '*')
        prefixSum[0] = 1;

    for(int i=1;i<n;i++)
    {
        if (s[i] == '*')
            prefixSum[i] = prefixSum[i - 1] + 1;
        else
            prefixSum[i] = prefixSum[i - 1];
    }

    vector<int> answer;

    for (auto& query : queries) {
        int start = nextCandle[query[0]];
        int end = prevCandle[query[1]];

    //This checks if there is no valid segment of the string with at least two plates (|) such that there can be candles (*) in between them.
        if (start >= end) {
            answer.push_back(0);
        } else {
            answer.push_back(prefixSum[end] - prefixSum[start]);
        }
    }

    return answer;
}
};

/*


Ex: s = "* * | * * | * * * |" , queries : [[2,5],[5,9]]
   
   -> First we preprocess and calculate index of prevCandle, nextCandle, 
   -> and count of '*' till current index in prefixSum vector
   
	index     :   0  1  2  3  4  5  6  7  8  9
	  s       :  '*  *  |  *  *  |  *  *  *  |'

	prev      :  -1 -1  2  2  2  5  5  5  5  9
	next      :   2  2  2  5  5  5  9  9  9  9

	prefixSum :   1  2  2  3  4  4  5  6  7  7
	
	0. query[0] = [2,5] 
			=> start = nextCandle[2] = 2
			=> end = prevCandle[5] =  5
			Thus, answer[0] = prefixSum[end] - prefixSum[start] = 4 - 2 = 2
			
	1. query[1] = [5,9] 
			=> start = nextCandle[5] = 5
			=> end = prevCandle[9] =  9
			Thus, answer[1] = prefixSum[end] - prefixSum[start] = 7 - 4 = 3

  */
