// NlogN using Rabin Karp + Binary Search
class RollingHash
{
private:
    const long long BASE1 = 31;
    const long long BASE2 = 37;

    const long long MOD1 = 1000000007;
    const long long MOD2 = 1000000009;

    vector<long long> pref1, pref2;
    vector<long long> power1, power2;

public:
    RollingHash(string& s)
    {
        int n = s.size();

        pref1.resize(n, 0);
        pref2.resize(n, 0);

        power1.resize(n, 1);
        power2.resize(n, 1);

        for(int i = 0; i < n; i++)
        {
            long long value = s[i] - 'a' + 1;

            if(i > 0)
            {
                power1[i] = power1[i - 1] * BASE1 % MOD1;
                power2[i] = power2[i - 1] * BASE2 % MOD2;

                pref1[i] = (pref1[i - 1] * BASE1 + value) % MOD1;
                pref2[i] = (pref2[i - 1] * BASE2 + value) % MOD2;
            }
            else
            {
                pref1[i] = value;
                pref2[i] = value;
            }
        }
    }

    pair<long long, long long> getHash(int l, int r)
    {
        int len = r - l + 1;

        long long h1 = pref1[r];
        long long h2 = pref2[r];

        if(l > 0)
        {
            h1 = (h1 - pref1[l - 1] * power1[len] % MOD1 + MOD1) % MOD1;
            h2 = (h2 - pref2[l - 1] * power2[len] % MOD2 + MOD2) % MOD2;
        }

        return {h1, h2};
    }
};

class Solution
{
public:
    bool check(RollingHash& rh, int n, int len)
    {
        set<pair<long long, long long>> seen;

        for(int i = 0; i + len <= n; i++)
        {
            auto hash = rh.getHash(i, i + len - 1);

            if(seen.count(hash))
            {
                return true;
            }

            seen.insert(hash);
        }

        return false;
    }

    int longestRepeatingSubstring(string s)
    {
        int n = s.size();

        RollingHash rh(s);

        int low = 1;
        int high = n - 1;
        int ans = 0;

        while(low <= high)
        {
            int mid = low + (high - low) / 2;

            if(check(rh, n, mid))
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return ans;
    }
};

/*

Try to find the given length of sub string at least 2 time, if found of length L , then try to minimize

use rolling hash for compare.

*/
