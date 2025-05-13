class Solution {
public:
   // approach 1
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Map to hold the sorted string as key and corresponding anagrams as value
        unordered_map<string, vector<string>> anagramGroups;

        for (const string& str : strs) {
            // Sort the string and use it as the key to group anagrams
            string sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end());

            // Add the original string to the corresponding group in the map
            anagramGroups[sortedStr].push_back(str);
        }

        // Convert the map values to a vector and return the result
        vector<vector<string>> result;
        for (auto& entry : anagramGroups) {
            result.push_back(entry.second);
        }

        return result;
    }

// approach 2
vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        unordered_map<string, vector<string>> map;
        vector<vector<string>> ret;
        for (const auto& s : strs) {
            string t = s;
            sort(t.begin(), t.end());
            map[t].push_back(s);
        }
        ret.reserve(map.size());
        for (auto& p : map) {
            ret.push_back(std::move(p.second));
        }
        return ret;
    }

// approach 3
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
      unordered_map<string, int> index;
      vector<vector<string>> result;
      for (string& s: strs) {
          string t = s;
          sort(t.begin(), t.end());
          if (index.find(t) == index.end()) { // new anagram
              index[t] = result.size();
              result.push_back({});
          }
          result[index[t]].push_back(s);
      }
      return result;
  }
};
