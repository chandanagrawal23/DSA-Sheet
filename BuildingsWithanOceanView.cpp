//https://leetcode.com/problems/buildings-with-an-ocean-view/
class Solution {
public:
    vector<int> findBuildings(vector<int>& a) {
        int n = a.size();
        stack<int  >st;
        vector<int >ans;

        for(int i=n-1;i>=0;i--)
        {
            while(!st.empty() and a[i]>st.top())
            {
                st.pop();
            }
            if(st.empty())
                ans.push_back(i);
            st.push(a[i]);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};


/*

class Solution {
    public int[] findBuildings(int[] heights) {
        int length = heights.length;
        boolean[] oceanView = new boolean[length];
        int count = 0;
        int maxHeight = 0;
        for (int i = length - 1; i >= 0; i--) {
            if (heights[i] > maxHeight) {
                oceanView[i] = true;
                count++;
            }
            maxHeight = Math.max(maxHeight, heights[i]);
        }
        int[] buildings = new int[count];
        int index = 0;
        for (int i = 0; i < length; i++) {
            if (oceanView[i])
                buildings[index++] = i;
        }
        return buildings;
    }
}

*/
