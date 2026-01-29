#include <bits/stdc++.h>
using namespace std;

// Node structure to store element value, its array number (row), and index inside that array
struct Node
{
    int value;
    int row;
    int index;

    // For minHeap: overload ">" so that priority_queue with greater<Node> works
    bool operator>(const Node &other) const
    {
        return value > other.value;
    }
};

// Function that returns {bestSet, bestDiff}
pair<vector<int>, int> smallestRangeSet(vector<vector<int>> &arrs)
{
    int k = arrs.size();
    for (auto &a : arrs)
        sort(a.begin(), a.end()); // sort each array

    // MinHeap of Node
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;

    int currentMax = INT_MIN;

    // Push first element from each array
    for (int i = 0; i < k; i++)
    {
        minHeap.push({arrs[i][0], i, 0});
        currentMax = max(currentMax, arrs[i][0]);
    }

    int bestDiff = INT_MAX;
    vector<int> bestSet;

    while (true)
    {
        Node mn = minHeap.top();
        minHeap.pop();

        int currentMin = mn.value;
        int diff = currentMax - currentMin;

        // Update answer if found better range
        if (diff < bestDiff)
        {
            bestDiff = diff;
            vector<int> temp(k);
            temp[mn.row] = mn.value;

            // Copy remaining heap values
            priority_queue<Node, vector<Node>, greater<Node>> copy = minHeap;
            while (!copy.empty())
            {
                Node n = copy.top();
                copy.pop();
                temp[n.row] = n.value;
            }
            temp[mn.row] = mn.value;
            bestSet = temp;
        }

        // If reached end of one array → break
        if (mn.index + 1 == arrs[mn.row].size())
            break;

        // Push next element from same array
        int nextVal = arrs[mn.row][mn.index + 1];
        minHeap.push({nextVal, mn.row, mn.index + 1});
        currentMax = max(currentMax, nextVal);
    }

    return {bestSet, bestDiff};
}

int main()
{
    vector<vector<int>> arr1 = {{7, 3, 9}, {5, 11, 6}, {8, 2, 10}};
    auto [set1, diff1] = smallestRangeSet(arr1);
    cout << "Best Set: ";
    for (int x : set1) cout << x << " ";
    cout << "\nBest Diff: " << diff1 << "\n";
    
    vector<vector<int>> arr2 = {{30, 1, 20}, {25, 15}, {28, 35, 17}, {40, 5, 27}};
    auto [set2, diff2] = smallestRangeSet(arr2);
    cout << "Best Set: ";
    for (int x : set2) cout << x << " ";
    cout << "\nBest Diff: " << diff2 << "\n";

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

// Node structure
struct Node
{
    int value;
    int row;
    int index;
};

// Custom comparator for minHeap
struct Compare
{
    bool operator()(const Node &a, const Node &b) const
    {
        return a.value > b.value; // smaller value has higher priority
    }
};

pair<vector<int>, int> smallestRangeSet(vector<vector<int>> &arrs)
{
    int k = arrs.size();
    for (auto &a : arrs)
        sort(a.begin(), a.end());

    // MinHeap using custom comparator
    priority_queue<Node, vector<Node>, Compare> minHeap;

    int currentMax = INT_MIN;

    // Push first elements
    for (int i = 0; i < k; i++)
    {
        minHeap.push({arrs[i][0], i, 0});
        currentMax = max(currentMax, arrs[i][0]);
    }

    int bestDiff = INT_MAX;
    vector<int> bestSet;

    while (true)
    {
        Node mn = minHeap.top();
        minHeap.pop();

        int currentMin = mn.value;
        int diff = currentMax - currentMin;

        if (diff < bestDiff)
        {
            bestDiff = diff;
            vector<int> temp(k);
            temp[mn.row] = mn.value;

            // Copy heap contents
            priority_queue<Node, vector<Node>, Compare> copy = minHeap;
            while (!copy.empty())
            {
                Node n = copy.top();
                copy.pop();
                temp[n.row] = n.value;
            }
            temp[mn.row] = mn.value;
            bestSet = temp;
        }

        if (mn.index + 1 == arrs[mn.row].size())
            break;

        int nextVal = arrs[mn.row][mn.index + 1];
        minHeap.push({nextVal, mn.row, mn.index + 1});
        currentMax = max(currentMax, nextVal);
    }

    return {bestSet, bestDiff};
}

int main()
{
    vector<vector<int>> arr1 = {{7, 3, 9}, {5, 11, 6}, {8, 2, 10}};
    auto [set1, diff1] = smallestRangeSet(arr1);
    cout << "Best Set: ";
    for (int x : set1) cout << x << " ";
    cout << "\nBest Diff: " << diff1 << "\n";

    vector<vector<int>> arr2 = {{30, 1, 20}, {25, 15}, {28, 35, 17}, {40, 5, 27}};
    auto [set2, diff2] = smallestRangeSet(arr2);
    cout << "Best Set: ";
    for (int x : set2) cout << x << " ";
    cout << "\nBest Diff: " << diff2 << "\n";

    return 0;
}


/*
-------------------------------
Intuition:
We want to pick one element from each array such that (max - min) is minimized.
We maintain a minHeap to always know the smallest element among chosen ones, and a variable currentMax to know the largest.
At each step, diff = currentMax - currentMin. If this is better, update best answer.
Then, move forward in the array from which currentMin came.
Process stops when one array finishes.

-------------------------------
Dry Run (Example with actual Node pushes):

Input arrays:
A = {7,3,9}, B = {5,11,6}, C = {8,2,10}
After sorting:
A = {3,7,9}, B = {5,6,11}, C = {2,8,10}

Step 0: Push first element of each array into heap:
Push Node(3, 0, 0) → value=3, row=0, index=0
Push Node(5, 1, 0) → value=5, row=1, index=0
Push Node(2, 2, 0) → value=2, row=2, index=0
currentMax = max(3,5,2) = 5
Heap now: [Node(2,2,0), Node(5,1,0), Node(3,0,0)]  // minHeap by value

Step 1:
Pop min Node(2,2,0)
currentMin=2, currentMax=5 → diff=3 → bestDiff=3, bestSet=[3,5,2]
Push next from row 2 → Node(8,2,1)
currentMax = max(5,8)=8
Heap now: [Node(3,0,0), Node(5,1,0), Node(8,2,1)]

Step 2:
Pop min Node(3,0,0)
currentMin=3, currentMax=8 → diff=5 → worse → do not update
Push next from row 0 → Node(7,0,1)
currentMax = max(8,7)=8
Heap now: [Node(5,1,0), Node(8,2,1), Node(7,0,1)]

Step 3:
Pop min Node(5,1,0)
currentMin=5, currentMax=8 → diff=3 → same → can update
Push next from row 1 → Node(6,1,1)
currentMax = max(8,6)=8
Heap now: [Node(6,1,1), Node(8,2,1), Node(7,0,1)]

Step 4:
Pop min Node(6,1,1)
currentMin=6, currentMax=8 → diff=2 → better → bestDiff=2, bestSet=[7,6,8]
Push next from row 1 → Node(11,1,2)
currentMax = max(8,11)=11
Heap now: [Node(7,0,1), Node(8,2,1), Node(11,1,2)]

Step 5:
Pop min Node(7,0,1)
currentMin=7, currentMax=11 → diff=4 → worse
Push next from row 0 → Node(9,0,2)
currentMax = max(11,9)=11
Heap now: [Node(8,2,1), Node(11,1,2), Node(9,0,2)]

Step 6:
Pop min Node(8,2,1)
currentMin=8, currentMax=11 → diff=3 → worse
Push next from row 2 → Node(10,2,2)
currentMax = max(11,10)=11
Heap now: [Node(9,0,2), Node(11,1,2), Node(10,2,2)]

Step 7:
Pop min Node(9,0,2)
Reached end of row 0 → break

Final Answer:
BestDiff = 2
BestSet = [7,6,8]
-------------------------------

Time Complexity: O( k*(nLogn) + (k*n)logk )  (n = max element in any array, k=number of arrays)
Space Complexity: O(k) [ at any time we have only k element in heap ]
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int>> &arrays)
{
    int k = arrays.size();

    vector<pair<int, int>> nums;
    for (int i = 0; i < k; i++)
    {
        for (int val : arrays[i])
        {
            nums.push_back({val, i});
        }
    }

    sort(nums.begin(), nums.end());

    vector<int> freq(k, 0);
    int covered = 0;

    int l = 0;
    int minDiff = INT_MAX;
    int bestL = 0, bestR = 0;

    for (int r = 0; r < nums.size(); r++)
    {
        if (freq[nums[r].second] == 0)
            covered++;

        freq[nums[r].second]++;

        while (covered == k)
        {
            int diff = nums[r].first - nums[l].first;
            if (diff < minDiff)
            {
                minDiff = diff;
                bestL = l;
                bestR = r;
            }

            freq[nums[l].second]--;
            if (freq[nums[l].second] == 0)
                covered--;

            l++;
        }
    }

    vector<int> result(k, INT_MIN);
    for (int i = bestL; i <= bestR; i++)
    {
        result[nums[i].second] = nums[i].first;
    }

    for (int x : result)
        cout << x << " ";
    cout << "\n" << minDiff << "\n\n";
}

int main()
{
    // -------- Test Case 1 --------
    vector<vector<int>> tc1 = {
        {7, 3, 9},
        {5, 11, 6},
        {8, 2, 10}
    };

    // -------- Test Case 2 --------
    vector<vector<int>> tc2 = {
        {30, 1, 20},
        {25, 15},
        {28, 35, 17},
        {40, 5, 27}
    };

    // -------- Test Case 3 --------
    vector<vector<int>> tc3 = {
        {1, 5, 9},
        {3, 8, 12}
    };

    cout << "Test Case 1:\n";
    solve(tc1);

    cout << "Test Case 2:\n";
    solve(tc2);

    cout << "Test Case 3:\n";
    solve(tc3);

    return 0;
}

/*
Approach:
- Merge all elements with their array index
- Sort by value
- Use sliding window to cover all k arrays
- Minimize (max - min) range

Time Complexity: O(N log N)
Space Complexity: O(N + k)
*/

