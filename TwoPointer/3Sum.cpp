class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &a)
    {
        vector<vector<int>> ans;
        int n = a.size();

        if (n < 3)
        {
            return ans;
        }

        // sort the array
        sort(a.begin(), a.end());

        for (int i = 0; i < n - 2; i++)
        {
            if (i > 0 && a[i] == a[i - 1])
            {
                continue; // skip duplicates
            }

            int start = i + 1;
            int end = n - 1;

            while (start < end)
            {
                int sum = a[i] + a[start] + a[end];

                if (sum < 0)
                {
                    start++;
                }
                else if (sum > 0)
                {
                    end--;
                }
                else
                {
                    ans.push_back({a[i], a[start], a[end]});

                    // Skip duplicate elements
                    while (start + 1 < end && a[start] == a[start + 1])
                    {
                        start++;
                    }
                    while (end - 1 > start && a[end] == a[end - 1])
                    {
                        end--;
                    }

                    start++;
                    end--;
                }
            }
        }

        return ans;
    }
};

/*
Approach:
- First, sort the array to make it easier to avoid duplicates and apply the two-pointer technique.
- We aim to find all unique triplets (a[i], a[j], a[k]) such that a[i] + a[j] + a[k] == 0.

- Loop through the array using index `i` (0 to n-3):
    - Treat `a[i]` as the fixed element of the triplet.
    - Initialize two pointers:
        - `start = i + 1` (just after `i`)
        - `end = n - 1` (last index)
    - The goal is to find two numbers such that:
        a[start] + a[end] == -a[i]
        (i.e., together with a[i], they sum to zero)

- Inside the while loop (start < end):
    - Calculate the sum of the triplet: a[i] + a[start] + a[end]
    - If sum is less than 0:
        → Increase `start` to move toward higher numbers.
    - If sum is greater than 0:
        → Decrease `end` to move toward smaller numbers.
    - If sum is exactly 0:
        → A valid triplet is found, push it into the result.
        → Then skip over duplicates at both `start` and `end` to ensure triplets are unique.

- To avoid duplicate triplets:
    - Skip the current `i` if it's the same as the previous element.
    - Skip repeated values at `start` and `end` while moving the pointers.

Time Complexity: O(N log N + N^2) = O(N^2)
- O(N log N) for sorting the array.
- O(N^2) for the outer loop and the two-pointer traversal inside.

Space Complexity: O(1) (excluding the output)
- Sorting is done in-place.
- No extra data structures are used for computation.
*/
