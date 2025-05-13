class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) 
    {
        unordered_map<long long, pair<int, int>> map;

        for (int i = 0; i < s.size(); i++) 
        {
            if (s[i] == '0') 
            {
                map.insert({0LL, {i, i}}); // leading zero case
                continue;
            }

            long long num = 0LL;
            for (int j = i; j < s.size() && j < i + 32; j++) 
            {
                num = num * 2 + (s[j] - '0'); // binary to decimal
                if (!map.count(num)) 
                {
                    map[num] = {i, j}; // store first occurrence
                }
            }
        }

        vector<vector<int>> ans;
        for (auto& q : queries) 
        {
            int val = q[0] ^ q[1]; // target value
            if (map.count(val)) 
            {
                ans.push_back({map[val].first, map[val].second});
            } 
            else 
            {
                ans.push_back({-1, -1});
            }
        }

        return ans;
    }
};

/*

we have to find shortest substring whose decimal value let say "val" XOR first == second for each query 


means we want=>  

decimalVal ^ first = second

decimalVal ^ first ^first = second ^first

decimalVal = second ^ first [ as x ^ x = 0]

Also see clearly it is mentioned that first and second will be <= 10^9 means <= 2^32

what we can do we will store all the substring  (in decimal value) of all length from 1 to 32 only

and for each query we will check whether we have any decimalValue present which is equal to ( first ^ second ) in our map
*/
