class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& p) {
        int sum=0;
        for(int i=0;i<p.size()-1;i++){
            int dy = abs(p[i+1][1]-p[i][1]);
            int dx  = abs(p[i+1][0]-p[i][0]);           
            sum+=min(dy,dx)+(abs(dy-dx));
        }
        return sum;
    }
};
