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

        pref1.resize(n);
        pref2.resize(n);

        power1.resize(n + 1);
        power2.resize(n + 1);

        power1[0] = 1;
        power2[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            power1[i] = power1[i - 1] * BASE1 % MOD1;
            power2[i] = power2[i - 1] * BASE2 % MOD2;
        }

        for (int i = 0; i < n; i++)
        {
            int value = s[i] - 'a' + 1;

            if (i == 0)
            {
                pref1[i] = value;
                pref2[i] = value;
            }
            else
            {
                pref1[i] = (pref1[i - 1] * BASE1 + value) % MOD1;
                pref2[i] = (pref2[i - 1] * BASE2 + value) % MOD2;
            }
        }
    }

    pair<long long, long long> getHash(int l, int r)
    {
        long long hash1 = pref1[r];
        long long hash2 = pref2[r];

        if (l > 0)
        {
            int len = r - l + 1;

            hash1 = (hash1 - pref1[l - 1] * power1[len] % MOD1 + MOD1) % MOD1;
            hash2 = (hash2 - pref2[l - 1] * power2[len] % MOD2 + MOD2) % MOD2;
        }

        return {hash1, hash2};
    }
};

class Solution
{
private:
    bool check(string& s, RollingHash& rh, int len, int& start)
    {
        map<pair<long long, long long>, int> seen;

        int n = s.size();
        start = INT_MAX;

        bool found = false;

        for (int i = 0; i + len <= n; i++)
        {
            auto hash = rh.getHash(i, i + len - 1);

            if (seen.find(hash) == seen.end())
            {
                seen[hash] = i;
            }
            else
            {
                int prev = seen[hash];

                if (i >= prev + len)
                {
                    found = true;
                    start = min(start, prev);
                }
            }
        }

        return found;
    }

public:
    string longestSubstring(string s)
    {
        int n = s.size();

        RollingHash rh(s);

        int left = 1;
        int right = n / 2;

        int bestLen = 0;
        int bestStart = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int start = -1;

            if (check(s, rh, mid, start))
            {
                bestLen = mid;
                bestStart = start;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        if (bestLen == 0)
        {
            return "-1";
        }

        return s.substr(bestStart, bestLen);
    }
};

/*
Approach:
1. Double rolling hash se har substring ka hash calculate karte hain.
2. Binary search se maximum possible length find karte hain.
3. Har length ke liye map mein substring ka earliest index store karte hain.
4. Duplicate substring tabhi valid hai jab:
       currentIndex >= previousIndex + length
   Isse dono occurrences non-overlapping rehti hain.
5. Sabhi valid duplicates mein earliest first occurrence ka index choose karte hain.
6. Agar koi valid repeating substring nahi milti, "-1" return karte hain.

Time Complexity: O(n log^2 n)
Space Complexity: O(n)

Note:
- Double hashing collision ki probability bahut kam karta hai,
  lekin theoretically collision possible hai.
- map ki wajah se har binary-search check O(n log n) hai.
*/
