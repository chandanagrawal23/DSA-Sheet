class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &a, int target)
    {
        vector<vector<int>> ans;
        int n = a.size();

        if (n < 4)
        {
            return ans;
        }

        sort(a.begin(), a.end());

        for (int i = 0; i < n - 3; i++)
        {
            if (i > 0 && a[i] == a[i - 1])
            {
                continue; // skip duplicates for i
            }

            for (int j = i + 1; j < n - 2; j++)
            {
                if (j > i + 1 && a[j] == a[j - 1])
                {
                    continue; // skip duplicates for j
                }

                int start = j + 1;
                int end = n - 1;

                while (start < end)
                {
                    long long sum = 1LL * a[i] + a[j] + a[start] + a[end];

                    if (sum < target)
                    {
                        start++;
                    }
                    else if (sum > target)
                    {
                        end--;
                    }
                    else
                    {
                        ans.push_back({a[i], a[j], a[start], a[end]});

                        // skip duplicates for start
                        while (start + 1 < end && a[start] == a[start + 1])
                        {
                            start++;
                        }

                        // skip duplicates for end
                        while (end - 1 > start && a[end] == a[end - 1])
                        {
                            end--;
                        }

                        start++;
                        end--;
                    }
                }
            }
        }

        return ans;
    }
};

/*
Approach:
- Sort the array to make duplicate handling and two-pointer logic easier.
- Loop through array with two fixed pointers `i` and `j`:
    - For each combination of (a[i], a[j]), use two pointers (start, end) to find two more elements such that:
        a[i] + a[j] + a[start] + a[end] == target

- If the current sum is less than target → move start forward.
- If the sum is greater → move end backward.
- If the sum equals target → store result and skip duplicates.

- To ensure uniqueness:
    - Skip duplicates for `i`, `j`, `start`, and `end`.

Time Complexity: O(N^3)
- Outer loop on `i` and inner on `j` are O(N^2)
- Two-pointer search per (i,j) pair takes O(N)
→ Overall O(N^3)

Space Complexity: O(1) (excluding output)
- No extra space used except for output.
*/
