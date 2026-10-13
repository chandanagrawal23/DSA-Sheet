/*
O(N^2)
class Solution
{
private:
    int solve(int i,int j, string& s, string& t,vector<vector<int>>& dp)
    {
        if (i == s.size() || j == t.size())
        {
            return 0;
        }

        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        if (s[i] == t[j])
        {
            return dp[i][j] = 1 + solve(i + 1, j + 1, s, t, dp);
        }

        return dp[i][j] = 0;
    }

public:
    int longestCommonSubstring(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans = max(ans, solve(i, j, s, t, dp));
            }
        }

        return ans;
    }
    int minOperations(string initial, string target) 
    {
        int n = initial.size();
        int m = target.size();
        // basically n - lcsLength + m - lcsLength;
        return n+m-2*longestCommonSubstring(initial,target);
    }
};

*/

// Rabin Karp se LCSubstr nikal lo Expected time: (O((n+m)log(min(n,m)))

class RollingHash
{
private:
    const long long BASE = 31;
    const long long MOD = 1000000007;

    vector<long long> pref;
    vector<long long> power;

public:
    RollingHash(string& text)
    {
        int n = text.size();

        pref.resize(n);
        power.resize(n + 1);

        power[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            power[i] = (power[i - 1] * BASE) % MOD;
        }

        for (int i = 0; i < n; i++)
        {
            int value = text[i] - 'a' + 1;

            if (i == 0)
            {
                pref[i] = value;
            }
            else
            {
                pref[i] = (pref[i - 1] * BASE + value) % MOD;
            }
        }
    }

    long long getHash(int l, int r)
    {
        long long ans = pref[r];

        if (l > 0)
        {
            ans -= pref[l - 1] * power[r - l + 1] % MOD;
        }

        ans = (ans + MOD) % MOD;

        return ans;
    }
};

class Solution
{
private:
    bool check( RollingHash& hash1, RollingHash& hash2, int n, int m, int len)
    {
        unordered_set<long long> hashes;

        // Store all substring hashes of s having length len
        for (int i = 0; i + len <= n; i++)
        {
            int l = i;
            int r = i + len - 1;

            hashes.insert(hash1.getHash(l, r));
        }

        // Search for a matching substring hash in t
        for (int i = 0; i + len <= m; i++)
        {
            int l = i;
            int r = i + len - 1;

            if (hashes.count(hash2.getHash(l, r)))
            {
                return true;
            }
        }

        return false;
    }

public:
    int longestCommonSubstring(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        RollingHash hash1(s);
        RollingHash hash2(t);

        int left = 0;
        int right = min(n, m);

        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;

            if (check(hash1, hash2, n, m, mid))
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }

        return left;
    }

    int minOperations(string initial, string target) 
    {
        int n = initial.size();
        int m = target.size();
        // basically n - lcsLength + m - lcsLength;
        return n+m-2*longestCommonSubstring(initial,target);
    }
};
