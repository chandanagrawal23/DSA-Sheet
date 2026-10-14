
class Solution
{
public:
    bool canReach(int n, vector<vector<int>>& edges, int k, int money)
    {
        vector<vector<int>> adj(n);

        for(auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            // ham graph hi tab banayenge ki given money se kam ho hamari cost.
            if(cost <= money)
            {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        vector<int> dist(n, -1);
        queue<int> q;

        q.push(0);
        dist[0] = 0;

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            if(u == n - 1)
            {
                return dist[u] <= k;
            }

            for(int v : adj[u])
            {
                if(dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        return false;
    }

    int minCost(int n, vector<vector<int>>& edges, int k)
    {
        int low = 0;
        int high = 0;

        for(auto& edge : edges)
        {
            high = max(high, edge[2]);
        }

        // if(!canReach(n, edges, k, high))
        // {
        //     return -1;
        // }

        int ans = -1;

        while(low <= high)
        {
            int mid = low + (high - low) / 2;

            if(canReach(n, edges, k, mid)) //reach kr skte hai mid cost me wo bhi k edges se kam , to mid ko or kam
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        return ans;
    }
};
