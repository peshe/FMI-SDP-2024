#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> findCommonChars(std::vector<std::string> &words)
{
    std::vector<int> globalMin(26, INT_MAX);
    std::vector<int> currentCount(26, 0);

    for (const std::string &word : words)
    {
        fill(currentCount.begin(), currentCount.end(), 0);

        for (char c : word)
            currentCount[c - 'a']++;
        
        for (int i = 0; i < 26; i++)
            globalMin[i] = std::min(globalMin[i], currentCount[i]);
        
    }

    std::vector<std::string> result;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < globalMin[i]; j++)
        {
            result.push_back(std::string(1, 'a' + i));
        }
    }

    return result;
}

int main()
{
    std::vector<std::string> words = {"bella", "label", "roller"};
    std::vector<std::string> result = findCommonChars(words);

    std::cout << "Common characters: ";
    for (const std::string &s : result)
        std::cout << s << " ";
    std::cout << std::endl;
//-------------------------------------------------------------
    std::vector<std::string> words2 = {"cool", "lock", "cook"};
    result = findCommonChars(words2);

    std::cout << "Common characters: ";
    for (const std::string &s : result)
        std::cout << s << " ";
    std::cout << std::endl;

    return 0;
}