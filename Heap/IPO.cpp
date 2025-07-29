class Solution
{
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        int n = profits.size();
        vector<pair<int, int>> project;

        // Store projects as {capital_required, profit}
        for (int i = 0; i < n; i++)
        {
            project.push_back({capital[i], profits[i]});
        }

        // Sort by capital required (ascending)
        sort(project.begin(), project.end());

        priority_queue<int> PQ; // max-heap to choose highest profit project
        int i = 0;

        while (k--)
        {
            // Push all projects we can currently afford into heap
            while (i < n && project[i].first <= w)
            {
                PQ.push(project[i].second);
                i++;
            }

            // If no affordable project left, break early
            if (PQ.empty())
            {
                break;
            }

            // Pick the most profitable project and update capital
            w += PQ.top();
            PQ.pop();
        }

        return w;
    }
};

/*

Approach:
===========
We are given two arrays:
- capital[i] = capital required for ith project
- profits[i] = profit we earn from ith project

Goal:
- Start with initial capital w
- Pick at most k projects
- At each step, choose a project we can afford and that gives max profit
- Return final capital after at most k such decisions

Key Strategy:
-------------
1. Sort all projects by capital requirement
2. Use a max-heap to keep track of all affordable projects
   → Among all projects with capital[i] ≤ w, pick the one with max profit

Steps:
------
- Iterate through sorted projects and push affordable ones into max-heap.
- In each iteration:
    - Pick max profit from heap
    - Increase your capital
    - Repeat for k iterations or until no projects are affordable

Why this works:
---------------
- We greedily take the **most profitable** among **currently affordable** projects
- Sorting helps us efficiently track which projects become affordable as `w` increases

Time:  O(n log n + k log n)
      - n log n for sorting
      - Each heap push/pop is log n and we may do that up to n + k times
Space: O(n) for heap and storing projects

*/
