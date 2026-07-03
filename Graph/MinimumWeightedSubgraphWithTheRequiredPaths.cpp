class Solution {
public:

    vector<long long> dijkstra(int src, vector<vector<pair<int,int>>>& adj)
    {
        int n = adj.size();

        vector<long long> dist(n, LLONG_MAX);

        using pr = pair<long long,int>;
        priority_queue< pr , vector<pr>, greater<> > pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty())
        {
            auto [cost, node] = pq.top();
            pq.pop();

            if(cost > dist[node])
                continue;

            for(auto &[child, wt] : adj[node])
            {
                if(dist[child] > cost + wt)
                {
                    dist[child] = cost + wt;
                    pq.push({dist[child], child});
                }
            }
        }

        return dist;
    }

    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest)
    {
        vector<vector<pair<int,int>>> adj(n);

        vector<vector<pair<int,int>>> revAdj(n);

        for(auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            // Reverse graph
            revAdj[v].push_back({u, w});
        }


        // dist from src1 to every node
        vector<long long> dist1 = dijkstra(src1, adj);

        // dist from src2 to every node
        vector<long long> dist2 = dijkstra(src2, adj);

        // every node -> dest
        vector<long long> distDest = dijkstra(dest, revAdj);

        long long ans = LLONG_MAX;

        for(int i = 0; i < n; i++)
        {
            if(dist1[i] == LLONG_MAX)
                continue;

            if(dist2[i] == LLONG_MAX)
                continue;

            if(distDest[i] == LLONG_MAX)
                continue;

            ans = min(ans, dist1[i] + dist2[i] + distDest[i]);
        }

        return ans == LLONG_MAX ? -1 : ans;
    }
};

/*
------------------------------------ APPROACH ------------------------------------

Observation 1:
We need to find a minimum weight subgraph such that

    src1 -----> dest
    src2 -----> dest

both paths exist.

The important point is that both paths are allowed to SHARE edges.
Shared edges are counted only once in the subgraph weight.

-----------------------------------------------------------------------

Observation 2:

Suppose both paths merge at some node X.

            src1
              \
               \
                X ---------> dest
               /
              /
           src2

Then total cost becomes

    (src1 -> X)
  + (src2 -> X)
  + (X -> dest)

So if we know these three distances for every node X,
we can simply take the minimum.

-----------------------------------------------------------------------

Step 1:
Run Dijkstra from src1.

This gives

    dist1[i] = shortest distance from src1 to node i.

-----------------------------------------------------------------------

Step 2:
Run Dijkstra from src2.

This gives

    dist2[i] = shortest distance from src2 to node i.

-----------------------------------------------------------------------

Step 3:
Now we need

    node i ---> dest

for every node.

A naive solution would be:

For every node i,
run Dijkstra(i, dest).

This would require

    O(V * E logV)

which is impossible for n = 1e5.

-----------------------------------------------------------------------

Observation 3 (Main Trick)

Instead of finding

    every node -> dest

we reverse every edge.

Original graph

    A -----> B

Reverse graph

    A <----- B

Now run ONE Dijkstra from dest on the reverse graph.

Suppose reverse graph gives

    distDest[A] = 10

This actually means

    dest -----> A   (reverse graph)

which is equivalent to

    A -----> dest   (original graph)

Therefore,

    distDest[i]

stores the shortest distance from node i to dest
in the ORIGINAL graph.

This reduces complexity from

    O(V * E logV)

to

    O(E logV)

-----------------------------------------------------------------------

Step 4:
Now every node can act as the meeting point.

For every node i,

answer =
    dist1[i]
  + dist2[i]
  + distDest[i]

Take the minimum over all nodes.

Ignore nodes that are unreachable from
src1, src2 or cannot reach dest.

-----------------------------------------------------------------------

Time Complexity

Building Graph      : O(E)

Dijkstra(src1)      : O(E logV)

Dijkstra(src2)      : O(E logV)

Dijkstra(dest)      : O(E logV)

Final Traversal     : O(V)

Overall

    O(E logV)

Space Complexity

Adjacency List      : O(E)

Reverse Graph       : O(E)

Distance Arrays     : O(V)

Priority Queue      : O(V)

Overall

    O(V + E)

-----------------------------------------------------------------------

Pattern Learned

Whenever you see

        A ----\
                \
                 X -----> Destination
                /
        B ----/

Think immediately:

1. Dijkstra from A
2. Dijkstra from B
3. Reverse Graph
4. Dijkstra from Destination
5. Try every node as the meeting point

This is a very common advanced Dijkstra pattern.
*/
