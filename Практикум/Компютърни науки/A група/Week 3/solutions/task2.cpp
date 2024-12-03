#include <iostream>
#include <stack>

using namespace std;

int applyOperator(int a, int b, char c)
{
    switch (c)
    {
    case '/':
        return a / b;
    case '%':
        return a % b;
        if (!b)
            throw invalid_argument("division by 0");
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    default:
        throw invalid_argument("invalid operation");
    }
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
bool isOperator(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '/':
    case '%':
    case '*':
        return true;
    }
    return false;
}

int evalPostfix(const string &s)
{
    stack<int> numbers;
    int a, b;
    for (char c : s)
    {
        if (isDigit(c))
        {
            numbers.push(c - '0');
            continue;
        }
        if (isOperator(c))
        {
            if (numbers.size() < 2)
                throw invalid_argument("Invalid expression");
            b = numbers.top();
            numbers.pop();

            a = numbers.top();
            numbers.pop();

            numbers.push(applyOperator(a, b, c));
            continue;
        }
        if (c == ' ')
            continue;
        throw invalid_argument("Invalid expression");
    }
    if (numbers.size() != 1)
        throw invalid_argument("Invalid expression");
    return numbers.top();
}

int main()
{
    string s;
    getline(cin, s);
    cout << evalPostfix(s) << endl;
}

// 53+82-*+