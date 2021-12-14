class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        int l1x = rec1[0];
        int l1y = rec1[1];
        int r1x = rec1[2];
        int r1y = rec1[3];
        
        
        int l2x = rec2[0];
        int l2y = rec2[1];
        int r2x = rec2[2];
        int r2y = rec2[3];
        
        // not overlap
        if(l2x>=r1x or l1x>=r2x)
            return false;
        // not overlap
        if(r2y<=l1y or r1y<=l2y)
            return false;
        return true;
    }
};

//https://leetcode.com/problems/rectangle-overlap/
