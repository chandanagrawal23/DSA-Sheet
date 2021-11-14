/*

Description
------------

Given N and K, find all the N digit numbers whose absolute difference of consecutive digit is K.

Example:

Given N = 3 , K = 1

Answer: 32

Explanation: All  3 digit numbers whose absolute difference of consecutive digit is 1 are -

[101,121,123,210,212,232,234,321,323,343,345,432,434,454,456,543,545,565,567,654,656,676,678,765,767,787,789,876,878,898,987,989]

Given N = 2 , K = 4

Answer: 11

Explanation: All  2 digit numbers whose absolute difference of consecutive digit is 4 are -

[15,26,37,40,48,51,59,62,73,84,95]

 

Constraints : 1<=N<=20 , 0<=K<=9




Solutions
----------
The idea is let say we have to generate N digit number, start from the left-most digit.

The first digit (leftmost digit) have choices from 1 to 9, now for the second digit we have 2 choices either first digt + x ,  or first digit -x


1'st digit = i  [1<=i<=9]
2nd digit = i-x or i+x  [1<=(i-x)<=9 and 1<=(i+x)<=9)
and so on

So we can do via BFS , push all 1 digit numbers in the queue, now pop and add both valid digit numbers at the end of the popped number and push again until we find "N" digit number.

My solution : https://leetcode.com/playground/G4ChpiUs


*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
  public:
    bool valid(int n)
    {
        return n>=0 and n<=9;
    }
    
    int findKConsecutive(int n , int x)
    {
        queue<string>q;
            for(int i=1;i<=9;i++)
                q.push(to_string(i));
            int cnt=0;
            while(!q.empty())
            {
                string s = q.front();q.pop();
                if(s.size()==n)
                {    cnt++;
                     continue;
                }
                int last = s.back()-'0';
                if(valid(last-x))
                    q.push(s+char('0'+(last-x)));
                
                if(valid(last+x))
                    q.push(s+char('0'+(last+x)));
            }
        return cnt;
    }
};

int main()
{
    Solution obj;
    cout<<obj.findKConsecutive(10,3);  // n , x in input
    return 0;
}
