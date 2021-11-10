class Solution {
public:
    string removeDuplicates(string s) {
        // use string as stack
        string res = "";
        for (char& currentChar : s)
            if (res.size()>0 and currentChar == res.back())
                res.pop_back();
            else
                res.push_back(currentChar);
        return res;
    }
};
