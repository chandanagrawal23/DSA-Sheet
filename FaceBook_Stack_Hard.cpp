/*

You are given an array a of N integers. For each index i, you are required to determine the number of contiguous subarrays that fulfills the following conditions:
The value at index i must be the maximum element in the contiguous subarrays, and
These contiguous subarrays must either start from or end with i.

Output
An array where each index i contains an integer denoting the maximum number of contiguous subarrays of a[i]
Example:
a = [3, 4, 1, 6, 2]
output = [1, 3, 1, 5, 1]

Explanation:
For index 0 - [3] is the only contiguous subarray that starts (or ends) with 3, and the maximum value in this subarray is 3.
For index 1 - [4], [3, 4], [4, 1]
For index 2 -[1]
For index 3 - [6], [6, 2], [1, 6], [4, 1, 6], [3, 4, 1, 6]
For index 4 - [2]
So, the answer for the above input is [1, 3, 1, 5, 1]

*/

// Brute force -

vector<int> brute(vector<int> a)
{
    int n = a.size();
    vector<int> ans(n,1);  // initialise all values as 1 of size N
    for(int i=0;i<n;i++)
    {
        int current = a[i];
        int left = i-1;
        int right = i+1;

        while (left >= 0 && current > a[left]) {
            ans[i]++;
            left--;
        }

        while (right < n && current > a[right]) {
            ans[i]++;
            right++;
        }
    }
    return ans;
}

// Optimal Solution using Stack
vector<int> optimal(vector<int> a)
{
    int n = a.size();
    vector<int> ans(n,0);  // initialise all values as 1 of size N
    vector<int> left(n,1);
    vector<int> right(n,1);
    stack<int> st;
    for(int i=0;i<n;i++)
    {
        while(!st.empty() && a[st.top()] < a[i])
        {
            left[i] += left[st.top()];
            st.pop();
        }
        
        st.push(i);
    }
    
    while(!st.empty())
        st.pop();
    
    for(lli i=n-1;i>=0;i--)
    {
        while(!st.empty() && a[st.top()] < a[i])
        {
            right[i] += right[st.top()];
            st.pop();
        }
        
        st.push(i);
    }
    
    
    for(int i=0;i<n;i++)
    {
        ans[i] = left[i] + right[i] -1;  // -1 bcz we add 1 two times in left as well as in right
    }
    return ans;
}

int main(){
fastio
lli n;
cin>>n;
vector<int> a(n);
for(int i=0;i<n;i++)
{
    cin>>a[i];
}
cout<<"Brute->  ";
for(auto val : brute(a))
    cout<<val<<" ";
cout<<endl;
  
cout<<"Optimal->";
for(auto val : optimal(a))
    cout<<val<<" ";
cout<<endl;
  
return 0;
}

