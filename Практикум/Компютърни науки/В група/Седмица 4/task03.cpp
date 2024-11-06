#include <iostream>
#include <queue>
#include <string>

std::string firstNonRepeatingSymbol(const std::string& input)
{
    int cnts[26] = {0,};
    std::queue<char> q;
    std::string answer = "";

    for (const char el : input)
    {
        ++cnts[el - 'a'];
        q.push(el);

        while (!q.empty() && cnts[q.front() - 'a'] > 1)
            q.pop();
        
        if (q.empty()) answer += "-1 ";
        else
        {
            answer += q.front();
            answer += " ";
        }
    }

    return answer;
}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    std::cout << firstNonRepeatingSymbol(input) << std::endl;
    return 0;
}