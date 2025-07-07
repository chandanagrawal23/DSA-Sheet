class Solution 
{
public:
    void reverseString(vector<char>& s) 
    {
        int left = 0;
        int right = s.size() - 1;

        while (left < right)
        {
            swap(s[left], s[right]); // Swap characters
            left++;
            right--;
        }
    }
};

/*
Approach:
- Use two pointers: one from start, one from end.
- Swap characters while left < right.
- This reverses the array in-place.

Time Complexity: O(n)
Space Complexity: O(1)
*/


//==================================================================================

class Solution {
public:
    void reverseString(vector<char>& s) {
        reverse(s.begin(),s.end());
    }
};
