// solution complexuty k1[k2[k3[. . . .]]]
// k1*k2 *k3 *k4
// solution 1
class Solution {
public:
    string decodeString(string s) {
        stack<char> st;
        for(auto xt : s)
        {
            if(xt==']')
            {
                string ss  = "";
                while(!st.empty() and st.top()!='[')
                {
                    ss  = st.top()+ss;
                    st.pop();
                }
                st.pop();
                
                int count  = 0 ;
                int base = 1;
                
                while(!st.empty() and isdigit(st.top()))
                {
                    count = count + (st.top()-'0')*base;
                    base = base*10;
                    st.pop();
                }
                
                while(count--)
                {
                    for(auto xr : ss)
                        st.push(xr);
                }              
                
            }
            else
            {
                st.push(xt);
            }
        }
        
        string ans = "";
        
        while(!st.empty())
        {
            ans = st.top()+ans;
            st.pop();
        }
        
        return ans;
        
        
    }
};

// solution 2
class Solution {
public:
    string decodeString(string s) {
        stack<int>countStack;
        stack<string>stringStack;
        string curr = "";
        int k = 0;
        for(auto xt : s)
        {
            if(isdigit(xt))
            {
                k = k *10 + (xt-'0');
            }
            else if(xt=='[')
            {
                stringStack.push(curr);
                countStack.push(k);
                k=0;
                curr = "";
            }
            else if(xt==']')
            {
                string decoded = stringStack.top();stringStack.pop();
                int times = countStack.top(); countStack.pop();
                while(times--)
                {
                    decoded += curr;
                }
                curr = decoded;
                
            }
            else
            {
                curr += xt;
            }
        }
        return curr;
    }
};

/*

Iterate over the string s and process each character as follows:

Case 1) If the current character is a digit (0-9), append it to the number k.

Case 2) If the current character is a letter (a-z), append it to the currentString.

Case 3) If current character is a opening bracket [, push k and currentString intocountStack and stringStack respectively.

Case 4) Closing bracket ]: We must begin the decoding process,

We must decode the currentString. Pop currentK from the countStack and decode the pattern currentK[currentString]

As the stringStack contains the previously decoded string, pop the decodedString from the stringStack. Update the decodedString = decodedString + currentK[currentString]

Time Complexity: \mathcal{O}(\text{maxK} \cdot n)O(maxK⋅n), where \text{maxK}maxK is the maximum value of kk and nn is the length of a given string ss. We traverse a string of size nn and iterate kk times to decode each pattern of form \text{k[string]}k[string]. This gives us worst case time complexity as \mathcal{O}(\text{maxK} \cdot n)O(maxK⋅n).

*/
