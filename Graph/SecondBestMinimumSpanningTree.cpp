#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from, to, weight, index;
    bool inMST = false;
};

class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.resize(n, 0);
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return false;
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int numberOfNodes;
vector<vector<pair<int, int>>> mstTree;
vector<vector<int>> maxEdgeOnPath;

void dfs(int currentNode, int parentNode, int maxWeight, int sourceNode)
{
    maxEdgeOnPath[sourceNode][currentNode] = maxWeight;
    for (auto &neighbor : mstTree[currentNode])
    {
        int nextNode = neighbor.first;
        int weight = neighbor.second;
        if (nextNode != parentNode)
        {
            dfs(nextNode, currentNode, max(maxWeight, weight), sourceNode);
        }
    }
}

bool edgeComparator(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

int findSecondBestMST(int totalNodes, vector<Edge> &edges)
{
    numberOfNodes = totalNodes;
    sort(edges.begin(), edges.end(), edgeComparator);

    DSU dsu(numberOfNodes);
    int mstTotalWeight = 0;
    mstTree.assign(numberOfNodes, {});

    for (Edge &edge : edges)
    {
        if (dsu.unite(edge.from, edge.to))
        {
            edge.inMST = true;
            mstTotalWeight += edge.weight;
            mstTree[edge.from].push_back({edge.to, edge.weight});
            mstTree[edge.to].push_back({edge.from, edge.weight});
        }
    }

    maxEdgeOnPath.assign(numberOfNodes, vector<int>(numberOfNodes, 0));
    for (int i = 0; i < numberOfNodes; ++i)
    {
        dfs(i, -1, 0, i);
    }

    int secondBestWeight = INT_MAX;
    for (auto &edge : edges)
    {
        if (!edge.inMST)
        {
            int u = edge.from, v = edge.to, w = edge.weight;
            int maxInPath = maxEdgeOnPath[u][v];
            if (maxInPath == 0)
                continue;
            int candidateWeight = mstTotalWeight - maxInPath + w;
            if (candidateWeight > mstTotalWeight)
                secondBestWeight = min(secondBestWeight, candidateWeight);
        }
    }

    return (secondBestWeight == INT_MAX) ? -1 : secondBestWeight;
}

int main()
{
    int totalNodes = 4;
    vector<Edge> edges = {
        {0, 1, 1, 0},
        {0, 2, 2, 1},
        {0, 3, 3, 2},
        {1, 2, 2, 3},
        {1, 3, 3, 4},
        {2, 3, 1, 5}};

    int result = findSecondBestMST(totalNodes, edges);
    cout << "Second Best MST Cost: " << result << endl;
    return 0;
}

/*
Approach:
---------
1. Build MST using Kruskal’s algorithm and mark the edges used.
2. Construct MST tree and for every node, DFS to fill maxEdgeOnPath[u][v] = max edge between u and v.
3. Try every edge not in MST. Adding it forms a cycle.
   Find the max edge on that path and simulate replacing it.
4. Track the minimum cost that is strictly greater than the MST weight.
5. Return the second best MST cost.

Time Complexity:
----------------
- Kruskal’s MST: O(E log E)
- DFS from each node to compute maxEdgeOnPath: O(N^2)
- Trying all non-MST edges: O(E)

Space Complexity:
-----------------
- O(N^2) for maxEdgeOnPath
- O(N + E) for tree and DSU
*/
