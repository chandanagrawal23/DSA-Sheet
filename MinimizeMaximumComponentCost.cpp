#include <bits/stdc++.h>
using namespace std;

/** DSU (Disjoint Set Union) with union by rank and path compression **/
struct DSU 
{
    vector<int> parent, rank;

    DSU(int n) 
    {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); // Initially, each node is its own parent
    }

    int find(int x) 
    {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) 
    {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false; // Already in the same set

        // Union by rank
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else 
        {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k) 
    {
        // Step 1: Convert edge list to [weight, u, v] format for easy sorting by weight
        vector<array<int, 3>> edgeList;
        for (auto& e : edges) 
        {
            edgeList.push_back({e[2], e[0], e[1]}); // [weight, u, v]
        }

        // Step 2: Sort edges in increasing order of weights for Kruskal's MST
        sort(edgeList.begin(), edgeList.end());

        // Step 3: Use Kruskal’s algorithm to form MST
        DSU dsu(n);
        vector<int> mstWeights; // To store weights of edges included in MST

        for (auto& [w, u, v] : edgeList) 
        {
            if (dsu.unite(u, v)) 
            {
                mstWeights.push_back(w); // Edge added to MST
            }
        }

        // Step 4: Remove the (k - 1) most expensive edges to form k components
        sort(mstWeights.rbegin(), mstWeights.rend()); // Sort descending to easily remove largest weights

        // Edge case: If k > n, we can only make n components
        if (k > n) k = n;

        // Step 5: Return the (k - 1)-th largest weight removed, meaning the max weight left in MST
        // If we removed top (k - 1), then the k-th largest (index k-1) is the answer
        return (k - 1 < (int)mstWeights.size()) ? mstWeights[k - 1] : 0;
    }
};

/**
 *  Problem:
 * Given a connected undirected graph with edge weights, remove edges to form at most `k` connected components.
 * The cost of a component is defined as the maximum edge weight in it.
 * We need to **minimize the maximum cost** among all components formed after removing edges.
 *
 *  Intuition:
 * To minimize the maximum cost of any component, we should only keep the lightest possible edges
 * that still keep the nodes connected — this is exactly what a **Minimum Spanning Tree (MST)** provides.
 *
 *  Why build MST first?
 * - MST connects all `n` nodes using only `n - 1` edges with minimum total weight.
 * - Removing any edge from MST increases the number of connected components by 1.
 * - So to form exactly `k` components, we need to remove `k - 1` edges from MST.
 *
 *  Steps:
 * 1. Convert edges to `{weight, u, v}` form and sort them by weight.
 * 2. Build MST using Kruskal’s algorithm with DSU.
 * 3. Store the weights of edges used in the MST.
 * 4. Sort those weights in descending order.
 * 5. Remove the top (k - 1) weights to split MST into `k` components.
 * 
 *     Why remove the (k - 1) largest weights?
 *    - In an MST with `n - 1` edges, each edge connects two components.
 *    - Removing any edge breaks the tree into two parts, increasing the component count by 1.
 *    - To go from 1 component to k components, we must remove exactly (k - 1) edges.
 *    - By removing the **largest weight edges**, we ensure that the **maximum edge weight remaining**
 *      (which defines component cost) is as small as possible.
 *    - Removing smaller edges would leave heavier edges inside the components, increasing cost — which we don't want.
 *
 * 6. The next largest edge weight (i.e., `k - 1`-th in sorted list) is the minimum possible maximum cost.
 *
 *  Time Complexity:
 * - O(E log E) to sort edges
 * - O(E * α(N)) for DSU operations (α is inverse Ackermann, ~constant)
 * - O(N log N) to sort MST weights
 * => Total: O(E log E + N log N)
 *
 *  Space Complexity:
 * - O(N) for DSU
 * - O(N) for MST edge weights


ham chahe jitni edges remove kr skte hai

to dekho, ham sabse pehle minimum wieights wali edges se ek graph banayenge jisse poora graph connected ho yani ? MST banayenge

baki jo edges hogi haam aasani se delete kr denge

ab hamare pass me ek graph h (MST) jisme ham har node pe jaa skte , ab ham is graph ko todenge K parts me ( jesa wquestion ne bola)

yani ham k-1 edges remove krenge ( for example agar ek graph ko 2 part me divide krna hai to 1 edge delete krni hogu)

to batao ham konsi k-1 edges delete maare ? jo sabse badi weight ki hai MST me or sabse badi wali ko return krdo

ab delete ka matlb hamko delete krni nhi hai , simple answer dena hai delete krne ke bad konsi sabse badi bachegi

to simple MST ki edges ko descendng me sort kro or [k-1] weight ko return kro


MST ki edges in desceding - 

1-2 (10)
2-3 (9)
3-4 (8)
4-5 (7)

k = 2 ,  yani ham 2 part me delete krenge , yani 1 edge remove krenge yani 1st edge (between 1 and 2 remove hogi)
to sabse badi edge konsi bachi ? (2-3 wali?? right ) yani weight 9 is answer , yani MST[k-1] = MST[2-1] = MST[1] = 9

 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

class DSU 
{
public:
    vector<int> parent;
    int components;

    DSU(int n) 
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        components = n; // Initially, each node is its own component
    }

    int find(int x) 
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(int x, int y) 
    {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr)
        {
            return false;
        }
        parent[yr] = xr;
        components--; // One less component after union
        return true;
    }

    int getComponentCount() 
    {
        return components;
    }
};

class Solution 
{
public:
    // Check if we can build a graph using edges with weight <= mid
    // such that the number of connected components <= k
    bool check(int n, vector<vector<int>>& edges, int mid, int k) 
    {
        DSU dsu(n);
        for (auto& edge : edges) 
        {
            int u = edge[0], v = edge[1], w = edge[2];
            if (w <= mid) 
            {
                dsu.unite(u, v);
            }
        }
        return dsu.getComponentCount() <= k;
    }

    int minCost(int n, vector<vector<int>>& edges, int k) 
    {
        int low = 0, high = 1e6;
        int answer = -1;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (check(n, edges, mid, k))
            {
                answer = mid;        // Possible answer, try to minimize further
                high = mid - 1;
            }
            else
            {
                low = mid + 1;       // Too few edges allowed, try higher weight
            }
        }

        return answer;
    }
};



/**
 *  Problem:
 * Given a connected undirected graph, we are allowed to remove any number of edges
 * to form at most `k` connected components.
 * The cost of a component is the maximum edge weight inside that component.
 * We must return the **minimum possible value of the maximum component cost**.
 *
 *  Approach: Binary Search + DSU (Disjoint Set Union)
 *
 * 1. We binary search on the **maximum allowed edge weight (mid)**.
 * 2. For each mid:
 *    - Try to build a forest using only edges with weight <= mid.
 *    - Use DSU to **union** nodes and track the number of **components**.
 *    - If the number of components formed <= k, it is a valid candidate.
 * 3. Among all valid mid values, we want the **smallest** one.
 *
 *  Why this works:
 * - If a value of mid gives us ≤ k components, then all values > mid will too.
 * - So we can apply binary search to find the minimum valid mid.
 *
 *  check() Function:
 * - Uses DSU to form components by connecting edges with weight <= mid.
 * - Each union reduces the number of components.
 *
 *  Time Complexity:
 * - Binary Search: O(log(maxW)), where maxW = max edge weight (1e6)
 * - For each mid, we process all edges: O(E * α(N)), where α(N) ≈ 1 (inverse Ackermann)
 * - Total: O(E * log(maxW))
 *
 *  Space Complexity:
 * - O(N) for DSU parent array
 *
 *  Final Result:
 * - The minimum value of maximum component cost when we split into ≤ k components
 */

