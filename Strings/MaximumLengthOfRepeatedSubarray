
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
    RollingHash(vector<int>& nums)
    {
        int n = nums.size();

        pref1.resize(n + 1, 0);
        pref2.resize(n + 1, 0);

        power1.resize(n + 1, 1);
        power2.resize(n + 1, 1);

        for (int i = 0; i < n; i++)
        {
            long long value = nums[i] + 1LL;

            power1[i + 1] = power1[i] * BASE1 % MOD1;
            power2[i + 1] = power2[i] * BASE2 % MOD2;

            pref1[i + 1] = (pref1[i] * BASE1 + value) % MOD1;
            pref2[i + 1] = (pref2[i] * BASE2 + value) % MOD2;
        }
    }

    pair<long long, long long> getHash(int l, int r)
    {
        int len = r - l + 1;

        long long h1 =
            (pref1[r + 1] - pref1[l] * power1[len] % MOD1 + MOD1) % MOD1;

        long long h2 =
            (pref2[r + 1] - pref2[l] * power2[len] % MOD2 + MOD2) % MOD2;

        return {h1, h2};
    }
};

class Solution
{
private:
    bool check( RollingHash& hashA,RollingHash& hashB, int n, int m, int len)
    {
        set<pair<long long, long long>> seen;

        for (int i = 0; i + len <= n; i++)
        {
            seen.insert(hashA.getHash(i, i + len - 1));
        }

        for (int j = 0; j + len <= m; j++)
        {
            if (seen.count(hashB.getHash(j, j + len - 1)))
            {
                return true;
            }
        }

        return false;
    }

public:
    int findLength(vector<int>& A, vector<int>& B)
    {
        int n = A.size();
        int m = B.size();

        RollingHash hashA(A);
        RollingHash hashB(B);

        int left = 0;
        int right = min(n, m);
        int ans = 0;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (mid == 0 || check(hashA, hashB, n, m, mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return ans;
    }
};

/*
Approach:
1. Build double polynomial prefix hashes for both arrays.
2. Binary search the candidate common-subarray length.
3. For a candidate length L, hash every length-L subarray of A.
4. Store those hashes in a set.
5. Scan every length-L subarray of B and check whether its
   double hash exists in the set.
6. If a match exists, L is feasible; search for a larger length.
   Otherwise, search for a smaller length.
7. Return the maximum feasible length.

Time Complexity: Expected O((n + m) * log(min(n, m)))
Space Complexity: O(n + m)
*/
