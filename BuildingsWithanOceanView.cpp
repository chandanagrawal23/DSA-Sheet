// Approach 1: Linear Iteration

class Solution
{
public:
    vector<int> findBuildings(vector<int>& heights)
    {
        int n = heights.size();
        vector<int> answer;
        
        for (int current = 0; current < n; ++current)
        {
            // If the current building is taller, 
            // it will block the shorter building's ocean view to its left.
            // So we pop all the shorter buildings that have been added before.
            while (!answer.empty() && heights[answer.back()] <= heights[current])
            {
                answer.pop_back();
            }
            answer.push_back(current);
        }
        
        return answer;
    }
};

// Short approach:
// Traverse left to right and maintain increasing heights.
// Pop shorter/equal buildings from answer when current building taller.
// Time: O(n), Space: O(n)

// -------------------------------------------------------------

// Approach 2: Monotonic Stack

class Solution
{
public:
    vector<int> findBuildings(vector<int>& heights)
    {
        int n = heights.size();
        vector<int> answer;
        stack<int> st;
        
        for (int current = n - 1; current >= 0; --current)
        {
            // If the building to the right is smaller, pop it.
            while (!st.empty() && heights[st.top()] < heights[current])
            {
                st.pop();
            }
            
            // If stack empty, no building to the right blocking view.
            if (st.size() == 0)
            {
                answer.push_back(current);
            }
            
            // Push current building index.
            st.push(current);
        }
        
        reverse(answer.begin(), answer.end());
        return answer;
    }
};

// Short approach:
// Traverse right to left using stack to track taller buildings to the right.
// Push building if no taller building to right exists.
// Time: O(n), Space: O(n)

// -------------------------------------------------------------

// Approach 3: Monotonic Stack Space Optimization

class Solution
{
public:
    vector<int> findBuildings(vector<int>& heights)
    {
        int n = heights.size();
        vector<int> answer;
        int maxHeight = -1;
        
        for (int current = n - 1; current >= 0; --current)
        {
            // Push building if taller than any building to its right.
            if (maxHeight < heights[current])
            {
                answer.push_back(current);
                maxHeight = heights[current];
            }
        }
        
        reverse(answer.begin(), answer.end());
        return answer;
    }
};

// Short approach:
// Traverse right to left, track max height seen.
// Add building if taller than max height so far.
// Time: O(n), Space: O(n)



// Approach 4 : Just like we use monotonic stack in Next greater element from left to right we can do same here - 

class Solution 
{
public:
    vector<int> findBuildings(vector<int>& heights) 
    {
        int n = heights.size();
        vector<int> nge(n, -1);   // store index of next greater to right
        stack<int> st;            // will store indices
        
        for (int i = 0; i < n; ++i) 
        {
            // Pop all smaller or equal buildings
            while (!st.empty() && heights[st.top()] <= heights[i]) 
            {
                nge[st.top()] = i;  // i is next greater for st.top()
                st.pop();
            }
            st.push(i);
        }
        
        vector<int> answer;
        // Buildings without any taller building to right (NGE == -1)
        for (int i = 0; i < n; ++i) 
        {
            if (nge[i] == -1) 
                answer.push_back(i);
        }
        
        return answer;
    }
};

