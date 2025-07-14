/*-----------------------------------------------------         DSU CLASS        ----------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;

class DSU
{
public:
    vector<int> parent;
    vector<int> componentSize;
    int totalComponents;

    // Constructor: Initialize DSU for n elements
    DSU(int n)
    {
        parent.resize(n);
        componentSize.assign(n, 1); // Every element is its own set of size 1
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        totalComponents = n;
    }

    // Find representative of the component with path compression
    int find(int node)
    {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }

    // Union the components of u and v using union by size
    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false;

        // Attach smaller component under the larger one
        if (componentSize[rootU] >= componentSize[rootV])
        {
            parent[rootV] = rootU;
            componentSize[rootU] += componentSize[rootV];
        }
        else
        {
            parent[rootU] = rootV;
            componentSize[rootV] += componentSize[rootU];
        }

        totalComponents--;
        return true;
    }

    // Check if u and v are in the same component
    bool sameComponent(int u, int v)
    {
        return find(u) == find(v);
    }

    // Return the size of the component containing u
    int getSize(int u)
    {
        return componentSize[find(u)];
    }

    // Return the current number of disjoint sets
    int getComponentCount()
    {
        return totalComponents;
    }
};
class Solution
{
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accountList)
    {
        int n = accountList.size();
        DSU dsu(n);

        unordered_map<string, int> emailToIndex;

        // Step 1: Union accounts based on shared emails
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j < accountList[i].size(); j++)
            {
                string email = accountList[i][j];
                if (emailToIndex.find(email) == emailToIndex.end())
                {
                    emailToIndex[email] = i;
                }
                else
                {
                    dsu.unite(i, emailToIndex[email]);
                }
            }
        }

        // Step 2: Group emails under the root representative
        unordered_map<int, vector<string>> rootToEmails;
        for (auto& [email, idx] : emailToIndex)
        {
            int groupRoot = dsu.find(idx);
            rootToEmails[groupRoot].push_back(email);
        }

        // Step 3: Construct final merged account
        vector<vector<string>> mergedAccounts;
        for (auto& [group, emails] : rootToEmails)
        {
            vector<string> account;
            account.push_back(accountList[group][0]); // account name
            sort(emails.begin(), emails.end());
            account.insert(account.end(), emails.begin(), emails.end());
            mergedAccounts.push_back(account);
        }

        return mergedAccounts;
    }
};

/*
 Intuition & Approach:
------------------------
- Each account may contain multiple emails. If two accounts share an email, they belong to the same person.
- We treat each account as a node and union them using DSU whenever they share a common email.
- After processing all pairs, we group emails by their component representative and return the merged account.

 Steps:
1. For each account, map every email to its corresponding account index.
2. If an email has already been seen before, union the current account with the account already mapped.
3. After DSU completes, group all emails under their parent component.
4. Sort emails for each group and prepend the name to form the merged result.

 Time Complexity:
- O(N * K * α(N)), where:
  - N = number of accounts
  - K = average number of emails per account
  - α = inverse Ackermann function (very small)
  - Sorting the result contributes O(E log E), where E = total unique emails

 Space Complexity:
- O(N + E) for DSU and email mappings
*/
