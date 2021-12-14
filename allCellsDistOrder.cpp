class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<bool>>visited(R,vector<bool>(C,0));
        vector<vector<int>>result;
        int i = 0;
        queue<vector<int>>q;
        q.push({r0,c0});
        while (!q.empty()) {
          vector<int>cell = q.front();q.pop();
          int r = cell[0];
          int c = cell[1];

          if (r < 0 || r >= R || c < 0 || c >= C) {
            continue;
          }
          if (visited[r][c]) {
            continue;
          }

          result.push_back(cell);
          i++;
          visited[r][c] = true;

          q.push({r, c - 1});
          q.push({r, c + 1});
          q.push({r - 1, c});
          q.push({r + 1, c});
        }
        return result;
    }
};

