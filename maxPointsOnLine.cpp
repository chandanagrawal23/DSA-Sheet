/*class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n<=2)
            return n;
        int maxi = 2;
        for(int i=0;i<n;i++)
        {
            int X1 = points[i][0];
            int Y1 = points[i][1];
            
            for(int j=i+1;j<n;j++)
            {
                int X2 = points[j][0];
                int Y2 = points[j][1];
                
                int total =2;
                
                for(int k=0;k<n;k++)
                {
                    if(i!=k and j!=k)
                    {
                        int X3 = points[k][0];
                        int Y3 = points[k][1];
                        if((Y2-Y1)*(X3-X2) ==  (X2-X1)*(Y3-Y2))
                                total++;
                    }
                }
                
                maxi = max(maxi , total);
            }
        }
        return maxi;
    }
};

*/

/*
 slope of two points is - 
 
 y2 - y1
 ________
 x2 - x1 
 
 
 if another point x3 , y3 lie on same line , then slope must be equal so
 
  y2 - y1     y3-y2
 ________  == ______
 x2 - x1      x3 - x2
 
 
 cross multiply , so that we can handle denominator if it is zero 
 
 so check (y2-y1)*(x3-x2) ==  (x2-x1)*(y3-y2);



*/

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<string, int> counter;
            for (int j = i + 1; j < n; j++)
            {
                    int dx = points[j][0] - points[i][0];
                    int dy = points[j][1] - points[i][1];
                    int g = gcd(dx, dy);
                    counter[to_string(dx / g) + '/' + to_string(dy / g)]++;
            }
            for (auto p : counter) {
                ans = max(ans, p.second);
            }
        }
        return ans+1;
    }
private:
    int gcd(int a, int b) {
        while (b) {
            a = a % b;
            swap(a, b);
        }
        return a;
    }
};
//https://leetcode.com/problems/max-points-on-a-line/
