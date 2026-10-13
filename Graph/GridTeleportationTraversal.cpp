/*
class Solution
{
public:
    int minMoves(vector<string>& matrix)
    {
        int n = matrix.size(), m = matrix[0].size();

        vector<vector<pair<int, int>>> portal(26);

        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < m; c++)
            {
                char ch = matrix[r][c];
                if (ch >= 'A' && ch <= 'Z')
                    portal[ch - 'A'].push_back({r, c});
            }
        }

        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        vector<bool> expanded(26, false);

        using State = array<int,3>;
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty())
        {
            auto [d, r, c] = pq.top();
            pq.pop();

            if (d != dist[r][c])
                continue;

            if (r == n - 1 && c == m - 1)
                return d;

            char ch = matrix[r][c];

            if (ch >= 'A' && ch <= 'Z' && !expanded[ch - 'A'])
            {
                int id = ch - 'A';
                expanded[id] = true;

                for (auto [nr, nc] : portal[id])
                {
                    if (dist[nr][nc] > d)
                    {
                        dist[nr][nc] = d;
                        pq.push({d, nr, nc});
                    }
                }
            }

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k], nc = c + dc[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= m || matrix[nr][nc] == '#')
                    continue;

                if (dist[nr][nc] > d + 1)
                {
                    dist[nr][nc] = d + 1;
                    pq.push({d + 1, nr, nc});
                }
            }
        }

        return -1;
    }
};

*/

/*
Approach: Dijkstra + Lazy Portal Expansion

- n = rows, m = columns.
- portal[ch - 'A'] stores all coordinates of each letter.
- dist[r][c] stores the minimum moves needed to reach a cell.
- array<int, 3> stores {distance, row, column}.
- Normal movement costs 1; teleportation costs 0.
- Each portal letter is expanded only once, from its
  minimum-distance cell.
- Ignore stale priority-queue entries using dist[r][c].

Time: O(n * m * log(n * m))
Space: O(n * m)
*/


class Solution
{
public:
    int minMoves(vector<string>& matrix)
    {
        int n = matrix.size(), m = matrix[0].size();

        vector<vector<pair<int, int>>> portal(26);

        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < m; c++)
            {
                char ch = matrix[r][c];
                if (ch >= 'A' && ch <= 'Z')
                    portal[ch - 'A'].push_back({r, c});
            }
        }

        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        vector<bool> expanded(26, false);

        using State = array<int,3>;
        dq<State> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty())
        {
            auto [d, r, c] = dq.front(); dq.pop_front();

            if (d != dist[r][c])
                continue;

            if (r == n - 1 && c == m - 1)
                return d;

            char ch = matrix[r][c];

            if (ch >= 'A' && ch <= 'Z' && !expanded[ch - 'A'])
            {
                int id = ch - 'A';
                expanded[id] = true;

                for (auto [nr, nc] : portal[id])
                {
                    if (dist[nr][nc] > d)
                    {
                        dist[nr][nc] = d;
                        dq.push_front({d, nr, nc});
                    }
                }
            }

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k], nc = c + dc[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= m || matrix[nr][nc] == '#')
                    continue;

                if (dist[nr][nc] > d + 1)
                {
                    dist[nr][nc] = d + 1;
                    dq.push_back({d + 1, nr, nc});
                }
            }
        }

        return -1;
    }
};


/*
Approach: 0-1 BFS + Lazy Portal Expansion

- n = rows, m = columns.
- portal[ch - 'A'] stores all coordinates of each letter.
- dist[r][c] stores the minimum moves to reach a cell.
- array<int, 3> stores {distance, row, column}.
- Teleportation costs 0, so push_front().
- Normal movement costs 1, so push_back().
- Each portal letter is expanded only once.
- Ignore stale deque entries using dist[r][c].

Time: O(n * m)
Space: O(n * m)
*/
