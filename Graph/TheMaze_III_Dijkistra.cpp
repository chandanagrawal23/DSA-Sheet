class Solution
{
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole)
    {
        int m = maze.size(), n = maze[0].size();
        const int INF = INT_MAX;

        vector<vector<int>> dist(m, vector<int>(n, INF)); // Minimum distance
        vector<vector<string>> bestPath(m, vector<string>(n, "")); // Lexicographically smallest path

        int dr[] = {1, 0, 0, -1};
        int dc[] = {0, -1, 1, 0}; // Down, left, right, up
        char direction[] = {'d', 'l', 'r', 'u'};

        using State = tuple<int, string, int, int>; // {distance, path, row, col}
        priority_queue<State, vector<State>, greater<State>> pq; // Min-heap

        int sr = ball[0], sc = ball[1];
        dist[sr][sc] = 0;
        pq.push({0, "", sr, sc}); // Start from ball

        while (!pq.empty())
        {
            auto [d, path, r, c] = pq.top();
            pq.pop();

            if (d != dist[r][c] || path != bestPath[r][c])
                continue;                       // Skip outdated state

            if (r == hole[0] && c == hole[1])
                return path; // Optimal path found

            for (int dir = 0; dir < 4; dir++)
            {
                int nr = r, nc = c, steps = 0;

                while (true)
                {
                    int rr = nr + dr[dir], cc = nc + dc[dir];

                    if (rr < 0 || rr >= m || cc < 0 || cc >= n || maze[rr][cc] == 1)
                        break; // Wall or boundary

                    nr = rr;
                    nc = cc;
                    steps++;

                    if (nr == hole[0] && nc == hole[1])
                        break; // Stop at hole
                }

                if (steps == 0)
                    continue; // Cannot move

                int newDist = d + steps;
                string newPath = path + direction[dir];

                if (newDist < dist[nr][nc] || (newDist == dist[nr][nc] && newPath < bestPath[nr][nc]))
                {
                    dist[nr][nc] = newDist;
                    bestPath[nr][nc] = newPath;
                    pq.push({newDist, newPath, nr, nc}); // Update best state
                }
            }
        }

        return "impossible"; // Hole unreachable
    }
};
