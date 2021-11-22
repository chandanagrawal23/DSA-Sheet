// C++ implementation of largest triplet
// multiplication
#include <bits/stdc++.h>
using namespace std;
 
// Prints the product of three largest numbers
// in subarray arr[0..i]
void LargestTripletMultiplication(int arr[], int n)
{
    // call a priority queue
    priority_queue<int> q;
 
    // traversing the array
    for (int i = 0; i < n; i++) {
        // pushing arr[i] in the array
        q.push(arr[i]);
 
        // if less than three elements are present
        // in array print -1
        if (q.size() < 3)
            cout << "-1" << " ";
        else {
            // pop three largest elements
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            int z = q.top();
            q.pop();
 
            // Reinsert x, y, z in priority_queue
            int ans = x * y * z;
            cout << ans << " ";
            q.push(x);
            q.push(y);
            q.push(z);
        }
    }
    return;
}
 
// Driver Function
int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    LargestTripletMultiplication(arr, n);
    return 0;
}

//https://www.geeksforgeeks.org/largest-triplet-product-stream/
