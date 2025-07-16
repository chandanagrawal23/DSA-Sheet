class Solution
{
private:
    unordered_map<string, string> keyToValue;  // Maps each key to its corresponding substitution
    unordered_map<string, string> memo;        // Memoizes resolved values to avoid recomputation

public:
    string applySubstitutions(vector<vector<string>>& replacements, const string& text)
    {
        for (const auto& pair : replacements)
        {
            keyToValue[pair[0]] = pair[1];
        }

        return resolve(text);
    }

private:
    string resolve(const string& input)
    {
        // Find the position of the first '%' character which marks the beginning of a placeholder
        size_t start = input.find('%');
        
        // If there is no '%' in the string, there are no placeholders to resolve
        if (start == string::npos)
            return input;
        
        // Find the position of the next '%' character which marks the end of the placeholder
        size_t end = input.find('%', start + 1);
        
        // If there's no closing '%', treat the string as literal text (invalid placeholder)
        if (end == string::npos)
            return input;
        
        // Extract the key between the two '%' characters (excluding the '%' symbols)
        // Example: if input is "Hi %name%!", then key will be "name"
        string key = input.substr(start + 1, end - start - 1);


        // If no substitution found, it's an error
        if (!keyToValue.count(key))
            return "ERROR";

        // Memoize resolved value for current key
        if (!memo.count(key))
            memo[key] = resolve(keyToValue[key]);

        string resolvedValue = memo[key];

        // Recursively resolve the rest of the string after this key
        return input.substr(0, start) + resolvedValue + resolve(input.substr(end + 1));
    }
};

/*
🧠 Approach:

- We process a string with placeholders like "%key%" and recursively resolve them using a dictionary.
- For each key, we:
    1. Extract it using the position of '%' characters.
    2. Look it up in a key-value map.
    3. Replace "%key%" with its resolved value recursively.
- Memoization (`memo`) is used to avoid redundant recursive calls for already resolved keys.

Example:
replacements = {{"name", "John"}, {"greet", "Hello, %name%!"}}
text = "%greet%" → expands to → "Hello, John!"

🕓 Time Complexity:
- O(L * D), where L = length of string, D = max depth of substitutions
- With memoization, repeated keys don’t re-expand.

🗃️ Space Complexity:
- O(N) for key-value map and memo cache, where N is number of unique keys

*/
