class Solution 
{
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) 
    {
        int n = recipes.size();
        vector<string> result;

        // Map each ingredient to the recipes that depend on it
        unordered_map<string, vector<string>> adjList;

        // Keep track of how many ingredients each recipe still needs
        unordered_map<string, int> indegree;

        // Build the graph
        for (int i = 0; i < n; i++) 
        {
            for (string& ing : ingredients[i]) 
            {
                adjList[ing].push_back(recipes[i]);
                indegree[recipes[i]]++;
            }
        }

        // Initialize queue with all available supplies
        queue<string> q;
        for (string& item : supplies) 
        {
            q.push(item);
        }

        // Perform BFS (Topological Sort)
        while (!q.empty()) 
        {
            string current = q.front();
            q.pop();

            // Try making all recipes that depend on current item
            for (string& recipe : adjList[current]) 
            {
                indegree[recipe]--;

                if (indegree[recipe] == 0) 
                {
                    result.push_back(recipe);
                    q.push(recipe); // It becomes a supply for others
                }
            }
        }

        return result;
    }
};

/*
Approach:
---------
- Build a dependency graph (adjacency list) where each ingredient maps to the recipes that depend on it.
- Use an indegree map to count how many ingredients each recipe still needs before it can be made.
- Add all the initial supplies to a queue (these are ingredients we already have).
- Use BFS (Kahn's Topological Sort) to simulate the process:
    - For each available ingredient, reduce the indegree of all recipes that use it.
    - If a recipe's indegree becomes 0, we can now make it — add it to result and push it to queue.
- Continue this until the queue is empty.

Time Complexity:
----------------
- O(R + I), where R = number of recipes, I = total number of ingredients across all recipes.

Space Complexity:
-----------------
- O(R + I), for graph and indegree tracking.
*/
