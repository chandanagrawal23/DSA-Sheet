class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
       vector<vector<int>>mat(n,vector<int>(n,0));
        int m = mat[0].size();
        int l = 0;
        int r = m-1;
        int u = 0;
        int d = n-1;
        int val = 1;
        vector<int>ans(n*m);
        int index = 0;
        while(l<=r and u<=d)
        {
            for(int col=l;col<=r;col++)
                mat[u][col]=val++;
            u++;
            if(u>d)
                break;
            
            for(int row = u;row<=d;row++)
                mat[row][r]=val++;
            r--;
            if(r<l)
                break;
            
            for(int col=r;col>=l;col--)
                mat[d][col]=val++;
            d--;
            if(d<u)
                break;
            
            for(int row=d;row>=u;row--)
                mat[row][l]=val++;
            l++;
            if(l>u)
                break;
        }
        return mat;
    }
};
