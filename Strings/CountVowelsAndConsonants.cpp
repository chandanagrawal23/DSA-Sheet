#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    void countVowelsAndConsonants(const string& sentence)
    {
        int vowels = 0, consonants = 0;

        for (char ch : sentence)
        {
            // Convert to lowercase for uniform comparison
            char c = tolower(ch);

            // Check if alphabet
            if (c >= 'a' && c <= 'z')
            {
                // Vowel check
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    vowels++;
                else
                    consonants++;
            }
        }

        cout << "Vowels: " << vowels << endl;
        cout << "Consonants: " << consonants << endl;
    }
};

int main()
{
    Solution obj;
    string input;

    cout << "Enter a sentence: ";
    getline(cin, input);

    obj.countVowelsAndConsonants(input);

    return 0;
}

/*
Approach:
- Iterate each character of the string.
- Check if it's an alphabet: (a–z or A–Z).
- If vowel, increment vowels counter; else increment consonants.

Time Complexity: O(n), where n = length of sentence
Space Complexity: O(1)
*/
