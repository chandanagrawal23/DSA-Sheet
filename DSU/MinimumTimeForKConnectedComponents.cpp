// Binary Search + DSU 
class DSU 
{
public:
    vector<int> parent, size;
    int components;

    DSU(int n) 
    {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0); // for(int i=0;i<n;i++) parent[i] = i;
        components = n;
    }

    int find(int x) 
    {
        while (x != parent[x]) 
        {
            parent[x] = parent[parent[x]];  // path compression
            x = parent[x];
        }
        return x;
    }

    void union_set(int x, int y) 
    {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        components--;
    }
};

class Solution 
{
public:
    int minTime(int n, vector<vector<int>>& edges, int k) 
    {
        int lo = 0, hi = 0, ans = -1;
        for (auto& e : edges) 
            hi = max(hi, e[2]);  // max possible removal time

        while (lo <= hi) 
        {
            int mid = lo + (hi - lo) / 2;
            
            // check if after removing all edges with time <= mid,
            // we get at least k connected components
            if (canSplit(n, edges, k, mid)) 
            {
                ans = mid;
                hi = mid - 1;  // try smaller time
            }
            else
            {
                lo = mid + 1;  // need more disconnection
            }
        }
        return ans;
    }

    bool canSplit(int n, vector<vector<int>>& edges, int k, int maxAllowedTime) 
    {
        DSU dsu(n);
        for (auto& e : edges) 
        {
            // keep edge only if it survives beyond maxAllowedTime
            if (e[2] > maxAllowedTime) 
                dsu.union_set(e[0], e[1]);
        }
        return dsu.components >= k;
    }
};


/*
APPROACH:
----------
We need the minimum time `t` such that after removing all edges with time <= t,
the graph has at least `k` connected components.

1. Binary Search on time:
   - Let `lo = 0` and `hi = max(time among edges)`.
   - For a given `mid`, simulate edge removals:
     - Keep only those edges with time > mid.
     - Use DSU to count connected components.
   - If components >= k, we can try a smaller time (move left).
   - Otherwise, increase time (move right).

2. DSU (Disjoint Set Union):
   - Helps track connected components efficiently.
   - Initially, n components (each node separate).
   - Every union reduces component count.

3. Stopping condition:
   - Binary search converges to the smallest valid time.

TIME COMPLEXITY:
- Each `canSplit` call → O(n + m * α(n)), where m = number of edges, α = Inverse Ackermann.
- Binary search over max edge time (~30 steps since time ≤ 1e9).
- Total: O((n + m) * log(maxTime)).

SPACE COMPLEXITY:
- DSU arrays → O(n).
- Edge list → O(m).

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sorting + DSU 

class DSU 
{
public:
    vector<int> parent, size;
    int components;

    DSU(int n) 
    {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        components = n;
    }

    int find(int x) 
    {
        while (x != parent[x]) 
        {
            parent[x] = parent[parent[x]];  // path compression
            x = parent[x];
        }
        return x;
    }

    void union_set(int x, int y) 
    {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        components--;
    }
};

class Solution 
{
public:
    int minTime(int n, vector<vector<int>>& edges, int k) 
    {
        // sort edges by removal time in descending order
        sort(edges.begin(), edges.end(), [](auto &a, auto &b) 
        {
            return a[2] > b[2];
        });

        DSU dsu(n);

        for (auto &e : edges) 
        {
            dsu.union_set(e[0], e[1]);
            
            // once components < k, current edge time is answer
            if (dsu.components < k) 
                return e[2];
        }

        // already ≥ k components initially
        return 0;
    }
};


/*
APPROACH:
----------
We need the minimum time `t` such that after removing all edges with time <= t,
the graph has at least `k` connected components.

1. Sort edges in descending order of time.
   - This simulates the graph in reverse:
     at the beginning all edges are present,
     and as time decreases, edges "vanish".

2. Initialize DSU with n isolated nodes.
   - Initially, there are n components.

3. Traverse edges in descending order:
   - Keep merging endpoints of each edge (since edge still exists).
   - Each union reduces component count.
   - As soon as components < k,
     the current edge’s time is the minimum `t`.

4. Special case:
   - If the graph already has ≥ k components at start, return 0.

TIME COMPLEXITY:
- Sorting edges: O(m log m), where m = number of edges.
- DSU operations: O(m * α(n)), α ≈ constant.
- Total: O(m log m).

SPACE COMPLEXITY:
- DSU arrays → O(n).
- Edge list → O(m).

*/

