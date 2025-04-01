class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int leftMostCol = 0;
        int rightMostCol = m-1;
        int upperMostRow = 0;
        int downMostRow = n-1;
        vector<int>ans(n*m);
        int index = 0;
        while(leftMostCol<=rightMostCol and upperMostRow<=downMostRow)
        {
            for(int col=leftMostCol;col<=rightMostCol;col++)
                ans[index++] = mat[upperMostRow][col];
            upperMostRow++;
            if(upperMostRow>downMostRow)
                break;
            
            for(int row = upperMostRow;row<=downMostRow;row++)
                ans[index++]=mat[row][rightMostCol];
            rightMostCol--;
            if(rightMostCol<leftMostCol)
                break;
            
            for(int col=rightMostCol;col>=leftMostCol;col--)
                ans[index++] = mat[downMostRow][col];
            downMostRow--;
            if(downMostRow<upperMostRow)
                break;
            
            for(int row=downMostRow;row>=upperMostRow;row--)
                ans[index++] = mat[row][leftMostCol];
            leftMostCol++;
            if(leftMostCol>upperMostRow)
                break;
        }
        return ans;
    }
};
