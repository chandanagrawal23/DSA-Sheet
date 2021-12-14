class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        set<int>contains;
        for(auto xt : points)
            contains.insert(xt[0]*(1<<10)+xt[1]);
        int n  = points.size();
        // assume two points on diagonal , so that we can find the other two and check wthther they form rectangle
        int minArea = INT_MAX;
        for(int i=0;i<n;i++)
        {
            int X1 = points[i][0];
            int Y1 = points[i][1];
            
            for(int j=i+1;j<n;j++)
            {
                int X2 = points[j][0];
                int Y2 = points[j][1];
                
                if(contains.count(X1*(1<<10)+Y2) and contains.count(X2*(1<<10)+Y1))
                {
                    int area = abs(X1 -  X2) * abs(Y1 - Y2);
                    // area must be +ve;
                    if(area)
                        minArea = min(minArea , area);
                } 
            }
        }
        if(minArea == INT_MAX)
                   return 0;
        return minArea;
    }
};
//https://leetcode.com/problems/minimum-area-rectangle/

//Initially I am trying to find {x1,y1} in set which is too cosly , so instead of this // I insert x1 + (1<<10) + y1 , a hash value so that we will find more efficienlty.
