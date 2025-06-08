class Solution
{
public:
    string minWindow(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        if (m > n)
        {
            return "";
        }

        int left = m, right = n;        // window size range
        int ansLen = -1;
        int startIndex = -1;

        // Binary search on window size
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int idx = isValidWindow(s, t, mid);

            if (idx != -1)
            {
                ansLen = mid;
                startIndex = idx;
              
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        if (startIndex == -1)
        {
            return "";
        }

        return s.substr(startIndex, ansLen);
    }

private:
    // Check if a window of given length contains all characters of t
    int isValidWindow(string &s, string &t, int len)
    {
        vector<int> target(128, 0), window(128, 0);
        for (char c : t)
        {
            target[c]++;
        }

        for (int i = 0; i < len; ++i)
        {
            window[s[i]]++;
        }

        if (containsAll(window, target))
        {
            return 0;
        }

        // Slide the window
        for (int i = len; i < s.size(); ++i)
        {
            window[s[i - len]]--;
            window[s[i]]++;

            if (containsAll(window, target))
            {
                return i - len + 1;
            }
        }

        return -1;
    }

    // Check if window has all required characters
    bool containsAll(vector<int> &window, vector<int> &target)
    {
        for (int i = 0; i < 128; ++i)
        {
            if (window[i] < target[i])
            {
                return false;
            }
        }
        return true;
    }
};


/*---------------------------------------------------------------
 Short approach
 ---------------------------------------------------------------
 1. Binary-search on possible window length L (from |t| to |s|).
 2. For a given L, use a sliding window with frequency tables to 
    test if any substring of length L contains all characters of t 
    with the required multiplicities.
 3. If a valid window exists, shrink the search space leftward; 
    otherwise enlarge it rightward.
 4. The smallest L that passes the test gives the answer.

 Time complexity  : O(|s| · Σ · log|s|)  
                    (Σ = 128 constant, so effectively O(|s| log|s|))
 Space complexity : O(Σ) ≈ O(1)         (two fixed-size freq arrays)
-----------------------------------------------------------------*/
