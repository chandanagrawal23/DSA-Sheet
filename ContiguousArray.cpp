class Solution
{
public:
    int findMaxLength(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> arr(n);

        // Convert 0 → -1, keep 1 as it is
        for (int i = 0; i < n; i++)
        {
            arr[i] = (nums[i] == 0) ? -1 : 1;
        }

        unordered_map<int, int> firstSeen; // prefixSum → earliest index
        int prefixSum = 0, maxLen = 0;

        for (int i = 0; i < n; i++)
        {
            prefixSum += arr[i];

            if (prefixSum == 0)
            {
                maxLen = max(maxLen, i + 1); // subarray [0...i] has sum 0
            }
            else if (firstSeen.count(prefixSum))
            {
                int len = i - firstSeen[prefixSum];
                maxLen = max(maxLen, len);
            }
            else
            {
                firstSeen[prefixSum] = i; // store first occurrence only
            }
        }

        return maxLen;
    }
};

/*
APPROACH:
---------
- First transform nums: set 0 → -1, 1 → +1.
- Goal: find the longest subarray with sum == 0 (i.e., equal 1s and 0s).
- Use prefix sum + hashmap to track earliest index where each sum occurred.
- If the same prefix sum is seen again, subarray in between has sum 0.
- Handle full-prefix-zero case (i.e., prefixSum == 0) explicitly instead of presetting the map.

TIME: O(n)
SPACE: O(n)
*/

// Similar Question : 
// Longest sub-array with equal number of alphabets and numeric characters

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int longestBalancedSubarray(const string& s)
{
    int prefixSum = 0, maxLen = 0;
    unordered_map<int, int> seen;  // prefixSum → earliest index

    for (int i = 0; i < s.length(); i++)
    {
        // Convert alpha to +1 and digit to -1
        if (isalpha(s[i]))
        {
            prefixSum += 1;
        }
        else if (isdigit(s[i]))
        {
            prefixSum -= 1;
        }

        if (prefixSum == 0)
        {
            maxLen = max(maxLen, i + 1); // full prefix is balanced
        }
        else if (seen.count(prefixSum))
        {
            maxLen = max(maxLen, i - seen[prefixSum]); // subarray with sum = 0
        }
        else
        {
            seen[prefixSum] = i; // store first occurrence
        }
    }

    return maxLen;
}

int main()
{
    string s = "a1b2c3x5m";
    cout << "Longest subarray length with equal alphabets and digits: "
         << longestBalancedSubarray(s) << endl;

    return 0;
}

/*
APPROACH:
---------
- Treat alphabets as +1, digits as -1.
- Problem reduces to finding longest subarray with sum = 0.
- Use prefix sum + hashmap to track first occurrence of each sum.
- If same sum seen again, subarray in between is balanced.
- Handle full-prefix case separately when prefixSum becomes 0.
- No need to pre-fill seen[0] = -1; we handle it via (prefixSum == 0).

TIME: O(n)
SPACE: O(n)
*/



// Similar Question : 
// Longest Subarray with Equal Number of 'a' and 'b'"

#include <iostream>
#include <unordered_map>
using namespace std;

int longestEqualAB(const string& s)
{
    int prefixSum = 0, maxLen = 0;
    unordered_map<int, int> firstSeen;  // prefixSum → first index

    for (int i = 0; i < s.length(); i++)
    {
        // Convert 'a' to +1 and 'b' to -1
        if (s[i] == 'a') 
            prefixSum += 1;
        else if (s[i] == 'b') 
            prefixSum -= 1;

        if (prefixSum == 0)
        {
            maxLen = max(maxLen, i + 1);  // entire prefix is balanced
        }
        else if (firstSeen.count(prefixSum))
        {
            maxLen = max(maxLen, i - firstSeen[prefixSum]);
        }
        else
        {
            firstSeen[prefixSum] = i;  // store first occurrence
        }
    }

    return maxLen;
}

int main()
{
    string s = "aabbaababbbba";
    cout << "Longest subarray with equal 'a' and 'b': "
         << longestEqualAB(s) << endl;

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// IMPO : Longest Substring with equal A , B and C

#include <iostream>
#include <unordered_map>
using namespace std;

int longestEqualABC(const string& s)
{
    unordered_map<string, int> seen; // key = "diffB-diffC", value = index
    int a = 0, b = 0, c = 0;
    int maxLen = 0;

    // Difference of counts
    int diffBA = 0, diffCA = 0;

    // base case: diff(0,0) seen at index -1
    seen["0#0"] = -1;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'a') a++;
        if (s[i] == 'b') b++;
        if (s[i] == 'c') c++;

        diffBA = b - a;
        diffCA = c - a;

        string key = to_string(diffBA) + "#" + to_string(diffCA);

        if (seen.count(key))
        {
            maxLen = max(maxLen, i - seen[key]);
        }
        else
        {
            seen[key] = i;
        }
    }

    return maxLen;
}

int main()
{
    string s = "abccbabcaacbb";
    cout << "Longest subarray with equal a, b, c: "
         << longestEqualABC(s) << endl;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPO : Longest Substring with equal A , B, C and D
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int longestBalancedABCD(const string& s)
{
    unordered_map<string, int> seen;  // key = diff_ba#diff_ca#diff_da
    int a = 0, b = 0, c = 0, d = 0;
    int maxLen = 0;

    seen["0#0#0"] = -1;  // to handle whole prefix match

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == 'a') ++a;
        else if (s[i] == 'b') ++b;
        else if (s[i] == 'c') ++c;
        else if (s[i] == 'd') ++d;

        // Differences from 'a'
        int diff_ba = b - a;
        int diff_ca = c - a;
        int diff_da = d - a;

        string key = to_string(diff_ba) + "#" + to_string(diff_ca) + "#" + to_string(diff_da);

        if (seen.count(key))
        {
            maxLen = max(maxLen, i - seen[key]);
        }
        else
        {
            seen[key] = i;
        }
    }

    return maxLen;
}

int main()
{
    string s = "abdcbdacabcd";
    cout << "Longest substring with equal number of a, b, c, d: " << longestBalancedABCD(s) << endl;
    return 0;
}
