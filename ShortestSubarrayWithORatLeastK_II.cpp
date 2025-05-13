class Solution 
{
public:
    // Helper function to perform OR operation by updating orval[] and returning the combined value
    int doOR(vector<int>& orval, int b) 
    {
        int ans = 0;

        for (int i = 31; i >= 0; i--) 
        {
            if ((1 << i) & b)
            {
                orval[i]++;
            }

            if (orval[i]) 
            {
                ans |= (1 << i);
            }
        }

        return ans;
    }

    // Helper function to reverse the effect of OR by decrementing orval[] and recomputing combined value
    int doUnOR(vector<int>& orval, int b) 
    {
        int ans = 0;

        for (int i = 31; i >= 0; i--) 
        {
            if ((1 << i) & b)
            {
                orval[i]--;
            }

            if (orval[i]) 
            {
                ans |= (1 << i);
            }
        }

        return ans;
    }

    int minimumSubarrayLength(vector<int>& a, int k) 
    {
        if (k == 0)
        {
            return 1;
        }

        int left = 0, right = 0;
        int n = a.size();
        int val = 0;
        vector<int> orval(32, 0);  // Store frequency of set bits at each bit position
        int ans = INT_MAX;

        while (right < n) 
        {
            // Add a[right] to the current OR value
            val = doOR(orval, a[right]);

            // Try shrinking the window from the left if OR is already >= k
            while (val >= k) 
            {
                ans = min(ans, right - left + 1);

                // Remove a[left] from OR calculation
                val = doUnOR(orval, a[left]);
                left++;
            }

            right++;
        }

        if (ans == INT_MAX)
        {
            return -1;
        }

        return ans;
    }
};
