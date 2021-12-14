class Solution {
public:
    bool isInside(int circle_x, int circle_y,
                   int rad, int x, int y)
    {
        if ((x - circle_x) * (x - circle_x) +(y - circle_y) * (y - circle_y) <= rad * rad)
            return true;
        else
            return false;
    }
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int>ans;
        for(auto circle : queries)
        {
            int x = circle[0];
            int y = circle[1];
            int r = circle[2];
            int cnt = 0;
            for(auto coordinate : points)
            {
                cnt+=(isInside(x,y,r,coordinate[0],coordinate[1]));
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};
//https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/
