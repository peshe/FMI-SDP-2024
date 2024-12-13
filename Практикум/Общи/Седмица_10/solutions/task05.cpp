class Solution {
public:
    constexpr static char SPACE = ' ';

    inline static string substring(const string& s, size_t start, size_t end) {
        return s.substr(start, end - start);
    }

    bool wordPattern(string pattern, string s) {
        set<char> charsEncountered;
        map<string, char> wordToChar;

        size_t currentWordStart = 0, currentWordEnd = 0;
        for (char c : pattern) {
            currentWordEnd = s.find(SPACE, currentWordStart);
            string currentWord = substring(s, currentWordStart, currentWordEnd);

            if (charsEncountered.count(c) == 0) {
                if (wordToChar.count(currentWord) == 0) {
                    charsEncountered.insert(c);
                    wordToChar[currentWord] = c;
                }
                else {
                    return false;
                }
            }
            else if (wordToChar[currentWord] != c) {
                return false;
            }

            currentWordStart = currentWordEnd + 1;
        }

        return (currentWordEnd == string::npos);
    }
};
