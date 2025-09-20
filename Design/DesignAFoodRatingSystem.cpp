#include <bits/stdc++.h>
using namespace std;

class FoodRatings
{
public:
    // cuisine -> set of { -rating, foodName } (sorted automatically: highest rating first, lexicographically smallest name if tie)
    unordered_map<string, set<pair<int, string>>> cuisineToFoods;

    // foodName -> cuisine
    unordered_map<string, string> foodToCuisine;

    // foodName -> rating
    unordered_map<string, int> foodToRating;

    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings)
    {
        for (int i = 0; i < foods.size(); ++i)
        {
            cuisineToFoods[cuisines[i]].insert({ -ratings[i], foods[i] });
            foodToCuisine[foods[i]] = cuisines[i];
            foodToRating[foods[i]] = ratings[i];
        }
    }

    void changeRating(string food, int newRating)
    {
        string cuisine = foodToCuisine[food];
        // remove old rating entry
        cuisineToFoods[cuisine].erase({ -foodToRating[food], food });
        // insert updated rating
        cuisineToFoods[cuisine].insert({ -newRating, food });
        
        foodToRating[food] = newRating;
    }

    string highestRated(string cuisine)
    {
        return begin(cuisineToFoods[cuisine])->second; // top element = highest rated
    }
};

/*
APPROACH SECTION
----------------
1. Data Structures Used:
   - unordered_map<string, set<pair<int,string>>> cuisineToFoods:
       For each cuisine, stores all foods in a set sorted by (-rating, foodName).
       This ensures highest rating comes first, and ties are broken lexicographically.
   - unordered_map<string, string> foodToCuisine:
       Maps foodName to its cuisine for O(1) access during rating changes.
   - unordered_map<string, int> foodToRating:
       Stores current rating of each food for fast lookup.

2. Constructor FoodRatings(foods, cuisines, ratings):
   - Iterates over all foods and inserts them into cuisineToFoods set as (-rating, foodName).
   - Maps food to its cuisine and rating.

3. changeRating(food, newRating):
   - Get cuisine of the food.
   - Remove the old pair (-oldRating, food) from cuisineToFoods[cuisine].
   - Insert the new pair (-newRating, food).
   - Update foodToRating[food].

4. highestRated(cuisine):
   - Since set is sorted by (-rating, foodName), the first element is the highest rated food.
   - Return its foodName.

Time Complexity:
- Constructor: O(N log N), N = number of foods (due to set insertions)
- changeRating: O(log M), M = number of foods in that cuisine
- highestRated: O(1) (accessing begin of set)

Space Complexity:
- O(N), storing mappings and sets for all foods.

----------------
DRY RUN EXAMPLE
----------------
Foods: ["sushi","ramen","udon"]
Cuisines: ["japanese","japanese","japanese"]
Ratings: [5,3,4]

Step 1: Constructor
cuisineToFoods["japanese"] = { (-5,"sushi"), (-3,"ramen"), (-4,"udon") }
foodToCuisine: { "sushi":"japanese", "ramen":"japanese", "udon":"japanese" }
foodToRating: { "sushi":5, "ramen":3, "udon":4 }

Step 2: highestRated("japanese")
- set = {(-5,"sushi"), (-4,"udon"), (-3,"ramen")}
- highest = "sushi"

Step 3: changeRating("udon",6)
- remove old (-4,"udon") → set becomes {(-5,"sushi"), (-3,"ramen")}
- insert (-6,"udon") → set becomes {(-6,"udon"), (-5,"sushi"), (-3,"ramen")}
- foodToRating["udon"] = 6

Step 4: highestRated("japanese")
- set = {(-6,"udon"), (-5,"sushi"), (-3,"ramen")}
- highest = "udon"

Step 5: changeRating("sushi",6)
- remove old (-5,"sushi") → set = {(-6,"udon"), (-3,"ramen")}
- insert (-6,"sushi") → set = {(-6,"sushi"), (-6,"udon"), (-3,"ramen")}
- tie in rating: lexicographically smaller first
- highestRated("japanese") = "sushi"

// This demonstrates how set maintains order by (-rating, foodName) and allows O(log N) updates.
*/
