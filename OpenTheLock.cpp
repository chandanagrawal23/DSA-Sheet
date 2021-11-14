//https://leetcode.com/problems/open-the-lock/
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        set<string>deads(deadends.begin(),deadends.end());
        set<string>vis;
        queue<string>q;
        q.push("0000");
        if(deads.find("0000")!=deads.end())
            return -1;
        int operation = 0;
        while(!q.empty())
        {
            for(int j=q.size()-1;j>=0;j--)
            {
                string temp = q.front();q.pop();
                
                if(temp == target)
                    return operation;
                
                for(int i=0;i<4;i++)
                {
                    string ss1 = temp , ss2 = temp;
                    char ch = temp[i];
                    ss1[i] = ch== '9' ? '0' : ch+1;
                    ss2[i] = ch== '0' ? '9' : ch-1;
                    if(deads.find(ss1)==deads.end() and vis.find(ss1)==vis.end())
                    {
                        q.push(ss1);
                        vis.insert(ss1);
                    }

                    if(deads.find(ss2)==deads.end() and vis.find(ss2)==vis.end())
                    {
                        q.push(ss2);
                        vis.insert(ss2);
                    }

                }
            }
            operation++;
        }    
        return -1;
    }
};
