class Solution
{
public:
    bool canReach(vector<int>& arr, int start)
    {
        int n = arr.size();
        vector<bool> visited(n, false);  // Track visited indices to avoid cycles
        queue<int> q;
        q.push(start);

        while (!q.empty())
        {
            int index = q.front();
            q.pop();

            if (arr[index] == 0)
            {
                return true;  // Goal reached
            }

            visited[index] = true;

            // Jump left
            int left = index - arr[index];
            if (left >= 0 && !visited[left])
            {
                q.push(left);
            }

            // Jump right
            int right = index + arr[index];
            if (right < n && !visited[right])
            {
                q.push(right);
            }
        }

        return false;  // No path to a 0 found
    }
};

/*
Approach:
---------
- Use Breadth-First Search (BFS) starting from the given index.
- From each index, jump to either:
    → index - arr[index] (left)
    → index + arr[index] (right)
- Stop and return true as soon as we reach a cell containing 0.
- Track visited indices to avoid infinite loops or revisits.

Time Complexity: O(n)
- Each index is visited at most once.

Space Complexity: O(n)
- For the visited array and BFS queue.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// using recursion as well

unordered_set<int> vis;
class Solution
{
public:
    bool canReach(vector<int>& arr, int start)
    {
      if (st >= 0 && st < arr.size() && vis.insert(st).second) 
      {
        return arr[st] == 0 || canReach(arr, st + arr[st]) || canReach(arr, st - arr[st]);
      }
      return false;
    }
};


