/*

Question :  Hermione Magic Potion Encoding
=========================================

Problem Statement:
=================
Hermione is preparing a cheat-sheet for her Potions final exam. To brew a potion, she must combine ingredients in a specific order. 
Ingredients can be repeated multiple times.To save space on her cheat-sheet, Hermione wants to encode the potion sequence using the following rules:

1. She can write an ingredient character directly.
2. She can use a special symbol * which means “repeat everything from the beginning of the potion sequence so far”.

Given a string S representing the potion sequence, find the minimum number of characters required to encode it using the cheat-sheet rules.

Input Format
-------------

A single string S of length n (1 ≤ n ≤ 10^5) consisting of uppercase letters [A-Z] only.

Output Format
--------------

A single integer, the minimum number of characters needed to encode the potion sequence.

Constraints
-------------

1 ≤ |S| ≤ 10^5

S consists of uppercase English letters [A-Z].

Notes
------

The * operation always repeats the entire potion sequence built so far.

You cannot partially repeat; only the full prefix built so far can be repeated.

Multiple * can be used consecutively if the pattern allows.

Examples -

Example 1:
Input: "ABCABCABCABC"
Output: 5
Explanation: 
Original potion: A B C A B C A B C A B C
Encoded: ABC**
- "ABC" → first three chars
- "*" → repeat "ABC" → ABCABC
- "*" → repeat "ABCABC" → ABCABCABCABC
Total length = 5

Example 2:
Input: "ABCABCABC"
Output: 7
Explanation:
Original potion: A B C A B C A B C
Encoded: ABC*ABC
- "ABC" → first three chars
- "*" → repeat "ABC" → ABCABC
- "ABC" → add remaining three chars
Total length = 7

Example 3:
Input: "AAAAAA"
Output: 5
Explanation:
Original potion: A A A A A A
Encoded: A**AA
- "A" → first char
- "*" → repeat "A" → AA
- "*" → repeat "AA" → AAAA
- Remaining "AA" → add remaining characters → potion built: "AAAAAA"
Total length = 5
*/

//=========================================================================================================================

// O(N^2) approach
#include <bits/stdc++.h>
using namespace std;

int minimalSteps(const string &ingredients)
{
    int n = ingredients.size();
    if (n == 0)
        return 0;

    string result;
    result.push_back(ingredients[0]);
    int prefixLen = 1; // actual prefix length in original string

    int i = 1;
    while (i < n)
    {
        // means if s[0..prefixLen] == s[i,i+prefixLen]
       // let say preifxLen is 3 , in ABCABC,and we are at index 3 (A) , s[0..0+3] = ABC is same as s[3,3+3] = s[3,6] = ABC
        if (i + prefixLen <= ingredients.size() && ingredients.substr(0, prefixLen) == ingredients.substr(i, prefixLen))
        {
            result.push_back('*');
            i += prefixLen;     // jump ahead by prefix length
            prefixLen *= 2;     // prefix doubled
        }
        else
        {
            result.push_back(ingredients[i]);
            i++;
            prefixLen++;
        }
    }
    cout<<ingredients<<" -> "<<result<<" -> ";

    return result.size();
}

int main()
{
    cout << minimalSteps("ABCABCABCABC") << endl;   // Expected: 5 (ABC**)
    cout << minimalSteps("ABCABCABC") << endl;      // Expected: 7 (ABC*ABC)
    cout << minimalSteps("ABCDABCE") << endl;       // Expected: 8 (ABCDABCE)
    cout << minimalSteps("ABCABCE") << endl;        // Expected: 5 (ABC*E)
    cout << minimalSteps("AAAAAA") << endl;         // Expected: 5 (A**AA)
    cout << minimalSteps("AAAAAAAA") << endl;       // Expected: 4 (A***)
    return 0;
}

/*
Approach:
- Maintain a prefixLen to track actual prefix size in original string.
- Start with first character.
- While iterating:
    - If substring(0, prefixLen) matches substring(i, i+prefixLen), add '*', jump by prefixLen, and double prefixLen.
    - Otherwise, add current character and increase prefixLen by 1.
- Return the encoded result length.

Time Complexity: O(n^2) in worst case (due to substring comparisons).
Space Complexity: O(n) for result string.
*/

//===========================================================================================================================
// O(N) approach [Rabin Carp]
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9+7;
const ll base = 31;

// Compute prefix hashes and powers
void computeHashes(const string &s, vector<ll> &hashPrefix, vector<ll> &power)
{
    int n = s.size();
    hashPrefix[0] = s[0]-'A'+1;
    power[0] = 1;
    for(int i=1;i<n;i++)
    {
        power[i] = (power[i-1]*base)%mod;
        hashPrefix[i] = (hashPrefix[i-1]*base + (s[i]-'A'+1))%mod;
    }
}

// Get hash of substring s[l..r]
ll getHash(int l, int r, vector<ll> &hashPrefix, vector<ll> &power)
{
    if(l==0) return hashPrefix[r];
    ll val = (hashPrefix[r] - hashPrefix[l-1]*power[r-l+1]%mod + mod)%mod;
    return val;
}

int minimalStepsRK(const string &ingredients)
{
    int n = ingredients.size();
    if(n==0) 
    {
        return 0;
    }

    string result;
    result.push_back(ingredients[0]);

    vector<ll> hashPrefix(n), power(n);
    computeHashes(ingredients, hashPrefix, power);

    int prefixLen = 1;
    int i = 1;

    while(i<n)
    {
        // compact check: if prefix matches next substring
        if(i + prefixLen <= n && getHash(0, prefixLen-1, hashPrefix, power) == getHash(i, i+prefixLen-1, hashPrefix, power))
        {
            result.push_back('*');    // add repeat symbol
            i += prefixLen;           // jump ahead by prefix length
            prefixLen *= 2;           // double prefix length
        }
        else
        {
            result.push_back(ingredients[i]); // add current char
            i++;
            prefixLen++;
        }
    }

    cout<<ingredients<<" -> "<<result<<" -> ";
    return result.size();
}

int main()
{
    cout<<minimalStepsRK("ABCABCABCABC")<<endl;   // 5 (ABC**)
    cout<<minimalStepsRK("ABCABCABC")<<endl;      // 7 (ABC*ABC)
    cout<<minimalStepsRK("ABCDABCE")<<endl;       // 8 (ABCDABCE)
    cout<<minimalStepsRK("ABCABCE")<<endl;        // 5 (ABC*E)
    cout<<minimalStepsRK("AAAAAA")<<endl;         // 5 (A**AA)
    cout<<minimalStepsRK("AAAAAAAA")<<endl;       // 4 (A***)
}

/*
Short Approach:
- Maintain prefix length of encoded potion so far.
- Precompute prefix hashes and powers for O(1) substring comparison (Rabin-Karp).
- Iterate over string:
    - If current prefix matches next substring → add '*' → jump → double prefix length.
    - Else → add current character → increment prefix length by 1.
- Return final encoded length.

Time Complexity: O(n) expected (hash comparisons O(1))
Space Complexity: O(n) for hash arrays and result string
*/

