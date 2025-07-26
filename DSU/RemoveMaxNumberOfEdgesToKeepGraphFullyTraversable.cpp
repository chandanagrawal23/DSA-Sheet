class UnionFind {
    public:
        vector<int> parent, size;
        int components;
        UnionFind(int n) 
        {
            components = n;
            parent.resize(n + 1);
            size.resize(n + 1, 1);
            for (int i = 0; i <= n; ++i) {
                parent[i] = i;
            }
        }

        int find(int x) 
        {
            if (parent[x] != x) 
            {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        bool unite(int x, int y) 
        {
            int rootX = find(x);
            int rootY = find(y);
            
            if (rootX == rootY)
                return false;
            
            if (size[rootX] < size[rootY]) 
                swap(rootX, rootY);
            
            parent[rootY] = rootX;
            
            size[rootX] += size[rootY];
            
            components--;
            
            return true;
        }

        bool isConnected() 
        {
            return components == 1;
        }
};
        
class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) 
    {
        UnionFind alice(n), bob(n);
        int edgesRequired = 0;
        
        // Process type 3 edges first
        for (const auto& edge : edges) 
        {
            if (edge[0] == 3) 
            {
                bool aliceConnected = alice.unite(edge[1], edge[2]);
                bool bobConnected = bob.unite(edge[1], edge[2]);
                if (aliceConnected || bobConnected) 
                {
                    edgesRequired++;
                }
            }
        }
        
        // Process type 1 and type 2 edges
        for (const auto& edge : edges) 
        {
            if (edge[0] == 1 and alice.unite(edge[1], edge[2]))
                    edgesRequired++;

            else if (edge[0] == 2 and bob.unite(edge[1], edge[2]))
                    edgesRequired++;
        }
        
        // Make sure both are fully connected
        // means Alice can visit whole graph AND Bob also visit whole graph
        if (alice.isConnected() && bob.isConnected()) 
        {
            return edges.size() - edgesRequired;
        }
        
        return -1;
    }
};
/*
APPROACH:

This problem is about maximizing the number of edges we can remove from a graph while still ensuring that both Alice and Bob can fully traverse the graph.

We use Disjoint Set Union (DSU or Union-Find) to simulate how Alice and Bob build their spanning trees separately.

1. **UnionFind Structure**:
   - Maintains connected components using path compression and union by size.
   - `components` tells us how many separate parts the graph has.

2. **Processing Type 3 Edges First**:
   - These edges can be used by both Alice and Bob.
   - We try to `unite` them in **both** Alice's and Bob's DSUs.
   - If either Alice or Bob connects two new components using this edge, we increment `edgesRequired`.

3. **Processing Type 1 and Type 2 Edges**:
   - Type 1 → Alice only.
   - Type 2 → Bob only.
   - Again, we `unite` only if it connects new components, and increment `edgesRequired`.

4. **Final Check**:
   - Both Alice and Bob must be fully connected (i.e., have only one component each).
   - If either is not connected, return `-1` (not possible to fully traverse).
   - Otherwise, the number of **removable edges** is `total edges - edges used`.

TIME COMPLEXITY:
- Let `E = edges.size()` and `N = n` (number of nodes)
- Each union/find operation is nearly constant time (amortized α(N), inverse Ackermann function)
- Total time: O(E * α(N)) ≈ O(E)

SPACE COMPLEXITY:
- O(N) for each UnionFind instance: parent[], size[]
- Total space: O(N)

*/
