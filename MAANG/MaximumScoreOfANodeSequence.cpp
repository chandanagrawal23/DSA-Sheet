class Solution
{
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges)
    {
        int n = scores.size();
        vector<vector<int>> graph(n);
        vector<vector<int>> bestNeighbors(n);

        // build adjacency list
        for (auto& e : edges)
        {
            int u = e[0];
            int v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // for each node, store (score, neighbor) pairs and sort
        for (int i = 0; i < n; i++)
        {
            vector<pair<int, int>> temp;
            for (int nei : graph[i])
                temp.push_back({scores[nei], nei});

            // sort descending by score
            sort(temp.begin(), temp.end(), greater<pair<int, int>>());

            // keep only top 3 neighbors
            for (int j = 0; j < min(3, (int)temp.size()); j++)
                bestNeighbors[i].push_back(temp[j].second);
        }

        long long maxScore = -1;

        // try every edge (u, v) as middle pair
        for (auto& e : edges)
        {
            int u = e[0];
            int v = e[1];

            for (int x : bestNeighbors[u])
            {
                if (x == v) continue;

                for (int y : bestNeighbors[v])
                {
                    if (y == u || y == x) continue;

                    long long total = (long long)scores[u] + scores[v] + scores[x] + scores[y];
                    maxScore = max(maxScore, total);
                }
            }
        }

        return (int)maxScore;
    }
};

/*
APPROACH:
----------
We need a sequence of 4 connected nodes:  x - u - v - y

1. For each edge (u, v):
   Treat it as the center connection.
   Choose:
       x → one of the top 3 neighbors of u (not v)
       y → one of the top 3 neighbors of v (not u or x)

2. To find top neighbors efficiently:
   - Build adjacency list for all nodes.
   - For each node, create pairs {score, neighbor}.
   - Sort these pairs in descending order and keep top 3 neighbors.

3. For every edge, compute:
       score = scores[x] + scores[u] + scores[v] + scores[y]
   Track the maximum among all.

Why only top 3 neighbors?
- Only a few high-score neighbors can form the optimal combination.
- Reduces time complexity drastically while ensuring correctness.

Time Complexity:  O(m log m)
Space Complexity: O(n + m)
*/
