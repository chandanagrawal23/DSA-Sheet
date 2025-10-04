class Solution
{
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges)
    {
        int n = scores.size();

        // adjacency list storing top 3 neighbors (by score) for each node
        vector<vector<int>> bestNeighbors(n);

        // build adjacency
        vector<vector<int>> graph(n);
        for (auto& e : edges)
        {
            int u = e[0], v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // keep only top 3 neighbors for each node
        for (int i = 0; i < n; i++)
        {
            // sort neighbors by score (descending)
            sort(graph[i].begin(), graph[i].end(), [&](int a, int b)
            {
                return scores[a] > scores[b];
            });

            // keep at most 3 best neighbors
            for (int j = 0; j < min(3, (int)graph[i].size()); j++)
                bestNeighbors[i].push_back(graph[i][j]);
        }

        long long maxScore = -1;

        // iterate over all edges and try to form sequence of length 4
        for (auto& e : edges)
        {
            int u = e[0], v = e[1];

            // pick neighbor x of u and y of v
            for (int x : bestNeighbors[u])
            {
                if (x == v) continue; // avoid reusing node

                for (int y : bestNeighbors[v])
                {
                    if (y == u || y == x) continue;

                    long long score = (long long)scores[u] + scores[v] + scores[x] + scores[y];
                    maxScore = max(maxScore, score);
                }
            }
        }

        return (int)maxScore;
    }
};

/* APPROACH:
   We need a sequence of 4 nodes connected like x - u - v - y.
   So for every edge (u, v), treat it as the middle of the sequence.
   Then choose:
       x = one of the top 3 highest-score neighbors of u (not v),
       y = one of the top 3 highest-score neighbors of v (not u, not x).
   Calculate score = scores[x] + scores[u] + scores[v] + scores[y].
   Keep track of the maximum score.

   Why only top 3 neighbors?
   - Because we just need the maximum score sequence.
   - Checking all neighbors would be too slow, but only the top 3
     are enough to guarantee the maximum.

   Time Complexity: O(m log m) for sorting neighbors (m = number of edges).
   Then O(m) to check edges.
   Space Complexity: O(n + m).
*/
