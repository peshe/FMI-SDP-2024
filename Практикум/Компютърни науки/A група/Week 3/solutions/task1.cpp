#include <iostream>
#include <stack>

using namespace std;

char getOpeningBracket(char b)
{
    switch (b)
    {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    case '>':
        return '<';
    };
    return 0;
}

bool isCorrect(const string &s)
{
    stack<char> letters;
    for (int i = 0; i < s.size(); i++)
    {
        switch (s[i])
        {
        case '[':
        case '{':
        case '(':
        case '<':
            letters.push(s[i]);
            break;
        case ')':
        case ']':
        case '}':
        case '>':
        {
            if (letters.empty() || letters.top() != getOpeningBracket(s[i]))
                return false;
            else
                letters.pop();
        }
        break;
        };
    }
    return letters.empty();
}

int main()
{
    string s;
    getline(cin, s);
    cout << isCorrect(s) << endl;
}