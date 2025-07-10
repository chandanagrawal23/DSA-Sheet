#include<bits/stdc++.h>
using namespace std;
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
    vector<int> ans(n, 0);
    vector<int> left(n, 1);   // Count of elements to the left where a[i] is max
    vector<int> right(n, 1);  // Count of elements to the right where a[i] is max
    stack<int> st;

    // LEFT PASS: How far can we extend to the left
    for (int i = 0; i < n; i++)
    {
        // If current value is bigger than top value of stack,
        // it means a[i] is the new maximum, and all subarrays ending at i
        // can be extended by all subarrays that ended at st.top()
        // (because a[i] > a[st.top()], so a[i] remains the max)
        while (!st.empty() && a[st.top()] < a[i])
        {
            left[i] += left[st.top()];  // extend count
            st.pop();
        }
        // Push current index onto the stack
        st.push(i);
    }


    while (!st.empty()) st.pop(); // clear stack

    // RIGHT PASS: How far can we extend to the right
    for (int i = n - 1; i >= 0; i--)
    {
        // If current value is bigger than top value of stack,
        // it means a[i] is the maximum for subarrays starting at i
        // and we can extend those subarrays by absorbing all the subarrays
        // that started at st.top() (because a[i] > a[st.top()])
        // So, we add right[st.top()] to right[i]
        while (!st.empty() && a[st.top()] < a[i])
        {
            right[i] += right[st.top()];
            st.pop();
        }
        // Push current index onto the stack
        st.push(i);
    }


    // Final answer
    for (int i = 0; i < n; i++)
    {
        ans[i] = left[i] + right[i] - 1;  // -1 because a[i] counted twice
    }

    return ans;
}


/*
Problem:
For each index i in array a, count how many subarrays:
  - a[i] is the maximum
  - and subarray either starts or ends at i

Idea:
We extend as far left and right as possible where a[i] stays the max.
Use monotonic stacks to compute:
- left[i]: number of contiguous elements to the left (including i)
- right[i]: number of contiguous elements to the right (including i)
Then:
  ans[i] = left[i] + right[i] - 1

Time: O(n)
Space: O(n)

Example:
a = [3, 1, 2, 4, 1]

▶ LEFT PASS TABLE (going from left to right):

| i | a[i] | Stack Before | Action                                   | left[i] | Stack After |
|---|------|--------------|------------------------------------------|---------|-------------|
| 0 |  3   | []           | push 0                                   | 1       | [0]         |
| 1 |  1   | [0]          | push 1                                   | 1       | [0, 1]      |
| 2 |  2   | [0,1]        | pop 1 → push 2                           | 2       | [0, 2]      |
| 3 |  4   | [0,2]        | pop 2, pop 0 → push 3                    | 3       | [3]         |
| 4 |  1   | [3]          | push 4                                   | 1       | [3, 4]      |

Resulting left[]  = [1, 1, 2, 3, 1]


▶ RIGHT PASS TABLE (going from right to left):

| i | a[i] | Stack Before | Action                                   | right[i] | Stack After |
|---|------|--------------|------------------------------------------|----------|-------------|
| 4 |  1   | []           | push 4                                   | 1        | [4]         |
| 3 |  4   | [4]          | pop 4 → push 3                           | 2        | [3]         |
| 2 |  2   | [3]          | push 2                                   | 1        | [3, 2]      |
| 1 |  1   | [3,2]        | push 1                                   | 1        | [3,2,1]     |
| 0 |  3   | [3,2,1]      | pop 1, pop 2 → push 0                    | 3        | [3,0]       |

Resulting right[] = [3, 1, 1, 2, 1]


▶ Final ans[i] = left[i] + right[i] - 1

left[]  = [1, 1, 2, 3, 1]  
right[] = [3, 1, 1, 2, 1]  
ans[]   = [3, 1, 2, 4, 1]

So:
- Index 0: [3], [3,1], [3,1,2]
- Index 1: [1]
- Index 2: [2], [1,2]
- Index 3: [4], [4,1], [2,4], [2,4,1]
- Index 4: [1]
*/



void printVector(const vector<int>& v)
{
    for (int x : v)
        cout << x << " ";
    cout << endl;
}
int main()
{
    // Test Case 1
    vector<int> a1 = {3, 4, 1, 6, 2};
    cout << "Test Case 1: \n";
    cout<<"Brute: ";   printVector(brute(a1));
    cout<<"Optimal: "; printVector(optimal(a1));  // Expected: [1, 3, 1, 5, 1]

    // Test Case 2
    vector<int> a2 = {1, 2, 3, 2, 1};
    cout << "Test Case 2: \n";
    cout<<"Brute: ";   printVector(brute(a2));
    cout<<"Optimal: "; printVector(optimal(a2));  // Expected: [1, 2, 5, 2, 1]

    // Test Case 3
    vector<int> a3 = {2, 1, 4, 5, 1};
    cout << "Test Case 3: \n";
    cout<<"Brute: ";   printVector(brute(a3));
    cout<<"Optimal: "; printVector(optimal(a3));  // Expected: [1, 1, 2, 4, 1]

    return 0;
}

