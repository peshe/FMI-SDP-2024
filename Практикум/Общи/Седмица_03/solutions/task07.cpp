#include <iostream>
#include <stack>
#include <string>
#include <cctype>

std::string decodeString(const std::string& s) 
{
    std::stack<int> countStack;
    std::stack<std::string> strStack;
    std::string result = "";
    
    int count = 0;

    for (char ch : s) 
    {
        if (isdigit(ch)) 
        {
            count = count * 10 + (ch - '0');
        } 
        else if (ch == '[') 
        {
            countStack.push(count);
            count = 0;
            strStack.push(result);
            result = "";
        } 
        else if (ch == ']') 
        {
            int repeatCount = countStack.top();
            countStack.pop();
            std::string currentStr = result;
            
            for (int i = 1; i < repeatCount; i++) 
            {
                result += currentStr;
            }
            result = strStack.top() + result;
            strStack.pop();
        } 
        else 
        {
            result += ch;
        }
    }

    return result;
}

int main() {
    std::string s1 = "3[a]2[bc]";
    std::string s2 = "3[a2[c]]";

    std::cout << std::boolalpha << (decodeString(s1) == "aaabcbc") << std::endl;
    std::cout << std::boolalpha << (decodeString(s2) == "accaccacc") << std::endl;

    return 0;
}