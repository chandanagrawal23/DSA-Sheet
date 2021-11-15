class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<int> st;
        string result;
        for(auto& letter : s)
        {   
            int count = 1;
            
            if(!result.empty() && result.back() == letter)
                count += st.top();
            
            if(count == k)
            {
                for(int i = 0; i < k - 1; i++)
                {
                    st.pop();
                    result.pop_back();
                }                    
            }
            else
            {
                st.push(count);
                result.push_back(letter);
            }
        }
        
        return result;
    }
};
