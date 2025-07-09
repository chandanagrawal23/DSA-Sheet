class DSU
{
public:
    vector<int> parent;

    DSU(int n)
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // Initially, each node is its own parent paren[i] = i
    }

    int find(int u)
    {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    bool unite(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);

        if (pu != pv)
        {
            parent[pu] = pv;
            return true; // Union done
        }
        return false; // Already connected
    }
};

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<array<int, 3>> edges;

        // Generate all possible edges with their manhattan distances
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.push_back({dist, i, j});
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end());

        DSU dsu(n);
        int totalCost = 0;
        int edgesUsed = 0;

        // Pick the smallest edges while avoiding cycles
        for (auto &[cost, u, v] : edges)
        {
            if (dsu.unite(u, v))
            {
                totalCost += cost;
                edgesUsed++;

                if (edgesUsed == n - 1) 
                      break; // MST is complete
            }
        }

        return totalCost;
    }
};

/*
=============================
Approach: Kruskal's Algorithm + DSU
=============================
1. Create all possible edges between pairs of points with weight as manhattan distance.
2. Sort the edges based on cost.
3. Use Disjoint Set Union (DSU) to greedily pick the smallest edge that doesn't form a cycle.
4. Stop when we’ve added (n - 1) edges — that’s when we have a valid MST.

=============================
 Time Complexity:
=============================
- Edge generation: O(N^2)
- Sorting edges: O(N^2 * log N)
- DSU operations: O(α(N)) ≈ constant time (almost linear)
- Total: **O(N^2 * log N)**

=============================
 Space Complexity:
=============================
- O(N^2) for edge list
- O(N) for DSU parent array

=============================

*/
