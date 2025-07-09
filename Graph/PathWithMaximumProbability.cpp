class Solution 
{
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) 
    {
        // Adjacency list: node → {neighbor, success probability}
        vector<pair<int, double>> adj[n];

        for (int i = 0; i < edges.size(); i++) 
        {
            int u = edges[i][0], v = edges[i][1];
            double prob = succProb[i];
            adj[u].push_back({v, prob});
            adj[v].push_back({u, prob});
        }

        // Probability of reaching each node, initialized to 0
        vector<double> maxProb(n, 0.0);
        maxProb[start] = 1.0;

        // Max-heap: {probability, node}
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start});

        while (!pq.empty()) 
        {
            auto [currProb, node] = pq.top();
            pq.pop();

            // If reached the end node, return the probability
            if (node == end) 
            {
                return currProb;
            }

            for (auto& [neighbor, edgeProb] : adj[node]) 
            {
                double newProb = currProb * edgeProb;

                // Update if new probability is higher
                if (newProb > maxProb[neighbor]) 
                {
                    maxProb[neighbor] = newProb;
                    pq.push({newProb, neighbor});
                }
            }
        }

        return 0.0; // If no path exists
    }
};

/*
Approach:

- Treat the graph as a weighted graph with edge weights as probabilities.
- Goal: Maximize product of probabilities from `start` to `end`.
- Use a max-heap (priority_queue) and a greedy Dijkstra-style approach:
    - At each step, pick the node with the highest probability.
    - Update neighbor's probability only if it improves.
    - Stop early if we reach the target node (`end`).

Key Point:
- Instead of summing weights like in standard Dijkstra, we multiply probabilities.

Time Complexity:  O(E * log V)
  - E = number of edges, V = number of nodes.

Space Complexity: O(V + E)
  - For adjacency list and probability tracking.
*/
