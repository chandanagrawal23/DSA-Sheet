class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& arr)
    {
        // Sort the array in ascending order to process smaller asteroids first
        sort(arr.begin(), arr.end());
        
        int n = arr.size();
        long long m = mass*1LL;  // Convert mass to long long to handle potential overflow

        for (int i = 0; i < n; i++)
        {
            // If the current asteroid can be destroyed (its mass is less than or equal to the current mass)
            if (arr[i] <= m)
                m += arr[i]; 
            else
                return false;  // If the asteroid can't be destroyed, return false
        }
        
        // If all asteroids are destroyed, return true
        return true;
    }
};

// Approach:
// 1. First, sort the array of asteroids in ascending order to destroy the smaller ones first.
// 2. Then, iterate through each asteroid and check if the current mass is sufficient to destroy it.
//    - If yes, increase the mass by the asteroid's mass.
//    - If no, return false (as it cannot be destroyed).
// 3. Finally, if all asteroids are destroyed, return true.
