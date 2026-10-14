// O(N) preprocessing, O(1) per substring hash query

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

        for(int i = 1; i <= n; i++)
        {
            power[i] = (power[i - 1] * BASE) % MOD;
        }

        for(int i = 0; i < n; i++)
        {
            int value = text[i] - 'a' + 1;

            if(i == 0)
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

        if(l > 0)
        {
            ans -= pref[l - 1] * power[r - l + 1] % MOD;
        }

        ans = (ans + MOD) % MOD;

        return ans;
    }
};




// Double prefix

// O(N) preprocessing, O(1) per substring hash query
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
        long long h1 = pref1[r];
        long long h2 = pref2[r];

        if(l > 0)
        {
            int len = r - l + 1;

            h1 = (h1 - pref1[l - 1] * power1[len] % MOD1 + MOD1) % MOD1;
            h2 = (h2 - pref2[l - 1] * power2[len] % MOD2 + MOD2) % MOD2;
        }

        return {h1, h2};
    }
};
