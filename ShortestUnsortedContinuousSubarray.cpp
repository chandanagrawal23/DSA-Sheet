#include <bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////////
// 1. NORMAL APPROACH : Expand around left/right boundaries
///////////////////////////////////////////////////////////////////////

/*
Time: O(n)
Space: O(1)
Idea: Find first decreasing pairs from left & right, then expand the window by comparing min/max inside to the outer boundary
*/
vector<int> printUnsorted(vector<int> &arr) {
    int n = arr.size();
    int left = n + 1, right = -1;

    for(int i = 0; i < n - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            left = i;
            break;
        }
    }

    if(left == n + 1) return {0, 0};  // already sorted

    for(int i = n - 1; i > 0; i--) {
        if(arr[i] < arr[i - 1]) {
            right = i;
            break;
        }
    }

    int maxi = arr[left], mini = arr[left];
    for(int i = left + 1; i <= right; i++) {
        maxi = max(maxi, arr[i]);
        mini = min(mini, arr[i]);
    }

    for(int i = 0; i < left; i++) {
        if(arr[i] > mini) {
            left = i;
            break;
        }
    }

    for(int i = n - 1; i > right; i--) {
        if(arr[i] < maxi) {
            right = i;
            break;
        }
    }

    return {left, right};
}

/////////////////////////////////////////////////////////////
// 2. PREFIX-MIN & SUFFIX-MAX APPROACH
/////////////////////////////////////////////////////////////
/*
Time: O(n)
Space: O(n)
Idea: An element at i is in correct position if it’s ≤ min of suffix [i+1...n-1], and ≥ max of prefix [0...i-1].
*/

class PrefixMinMax {
public:
    int findUnsortedSubarray(vector<int>& a) {
        int n = a.size();
        vector<int> maxlhs(n), minrhs(n);
        int maxl = INT_MIN, minr = INT_MAX;

        for (int i = n - 1; i >= 0; i--) minrhs[i] = min(minr, a[i]), minr = min(minr, a[i]);
        for (int i = 0; i < n; i++) maxlhs[i] = max(maxl, a[i]), maxl = max(maxl, a[i]);

        int i = 0, j = n - 1;
        while (i < n && a[i] <= minrhs[i]) i++;
        while (j > i && a[j] >= maxlhs[j]) j--;

        return (j - i + 1);
    }
};

/////////////////////////////////////////////////////////////
// 3. MONOTONIC STACK APPROACH
/////////////////////////////////////////////////////////////

/*
Time: O(n)
Space: O(n)
Idea: Use two stacks:
- One to find leftmost index where order breaks
- One to find rightmost index where order breaks
*/

class MonoStackApproach {
public:
    int findUnsortedSubarray(vector<int>& a) {
        int n = a.size();
        stack<int> st;
        int l = n, r = -1;

        // Increasing stack to find left bound
        for(int i = 0; i < n; i++) {
            while(!st.empty() && a[st.top()] > a[i]) {
                l = min(l, st.top());
                st.pop();
            }
            st.push(i);
        }

        while(!st.empty()) st.pop();

        // Decreasing stack to find right bound
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && a[st.top()] < a[i]) {
                r = max(r, st.top());
                st.pop();
            }
            st.push(i);
        }

        return (l == n && r == -1) ? 0 : r - l + 1;
    }
};



/////////////////////////////////////////////////////////////
int main() {
    vector<int> arr = {0, 1, 15, 25, 6, 7, 30, 40, 50};
    vector<int> res = printUnsorted(arr);
    cout << "Unsorted Range using Normal Method: " << res[0] << " " << res[1] << "\n";

    PrefixMinMax pfx;
    cout << "Unsorted Length using PrefixMinMax: " << pfx.findUnsortedSubarray(arr) << "\n";

    MonoStackApproach mono;
    cout << "Unsorted Length using MonoStack: " << mono.findUnsortedSubarray(arr) << "\n";

    return 0;
}
