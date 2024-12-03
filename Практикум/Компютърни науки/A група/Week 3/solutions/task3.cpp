#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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

int getPriority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
        return 0;
    default:
        throw invalid_argument("Invalid expression22");
    }
}

bool validBrackets(const string &infix)
{
    int openBrackets = 0;
    for (char c : infix)
    {
        if (c == '(')
            openBrackets++;
        if (c == ')')
            openBrackets--;
        if (openBrackets < 0)
            return false;
    }
    return openBrackets == 0;
}

bool validSymbols(const string &infix)
{
    for (char c : infix)
        if (!(isOperator(c) || isLetter(c) || c == '(' || c == ')'))
            return false;

    return true;
}

bool validOperators(const string &infix)
{

    bool op = false;
    int i = 0;
    while (i < infix.size() && (infix[i] == ' ' || infix[i] == '('))
        i++;

    if (i == infix.size()) // Няма променливи и оператори
        return false;

    if (isOperator(infix[i])) // Първия символ различен от скоба и интервал е оператор
        return false;

    for (i = i + 1; i < infix.size(); i++)
    {
        if (infix[i] == ' ' || infix[i] == '(' || infix[i] == ')')
            continue;
        if ((!op && isLetter(infix[i])) || (op && isOperator(infix[i])))
            return false;
        op = !op;
    }
    return true;
}

bool isValidInfix(const string &infix)
{
    return infix.size() != 0 &&
           validBrackets(infix) &&
           validSymbols(infix) &&
           validOperators(infix);
}

string InfixToPostix(const string &infix)
{
    if (!isValidInfix(infix))
        throw invalid_argument("Invalid infix expression");
    
    string postfix = "";
    stack<char> operations;
    for (char c : infix)
    {
        if (isLetter(c))
            postfix += c;

        else if (c == '(')
            operations.push('(');

        else if (c == ')')
        {
            while (!operations.empty() && operations.top() != '(')
            {
                postfix += operations.top();
                operations.pop();
            }
            operations.pop();
        }
        else if (isOperator(c))
        {
            while (!operations.empty() && getPriority(c) <= getPriority(operations.top()))
            {
                postfix += operations.top();
                operations.pop();
            }
            operations.push(c);
        }
    }
    while (!operations.empty())
    {
        postfix += operations.top();
        operations.pop();
    }
    return postfix;
}

//-----------bonus---------
vector<char> getVariables(const string &s)
{
    bool usedLower[26]{0,}, usedUpper[26]{0,};
    for (char c : s)
    {
        if (c >= 'a' && c <= 'z')
            usedLower[c - 'a'] = true;
        if (c >= 'A' && c <= 'Z')
            usedUpper[c - 'A'] = true;
    }
    vector<char> res;
    for (int i = 0; i < 26; i++)
        if (usedLower[i])
            res.push_back((char)(i + 'a'));
    for (int i = 0; i < 26; i++)
        if (usedUpper[i])
            res.push_back((char)(i + 'A'));
    return res;
}

int applyOperator(int a, int b, char c)
{
    switch (c)
    {
        case '/':
            if (!b)
                throw invalid_argument("division by 0");
            return a / b;
        case '%':
            if (!b)
                throw invalid_argument("division by 0");
            return a % b;
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

size_t calculateIndex(char c)// 0-25 малки, 26-51 главни
{ 
    if (!isLetter(c))
        throw invalid_argument("Not a letter");
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return c - 'A' + 26;
}

int evalPostfix(const string &s, int *values)
{
    stack<int> numbers;
    int a, b, index;
    for (char c : s)
    {
        if (isLetter(c))
        {
            numbers.push(values[calculateIndex(c)]); //!!!
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

int calculateWithValues(const string &infix)
{
    vector<char> variables = getVariables(infix);

    int values[52] = {0,};
    for (char c : variables)
    {
        cout << "Enter value for " << c << ": ";
        cin >> values[calculateIndex(c)];
    }

    string postfix = InfixToPostix(infix);
    return evalPostfix(postfix, values);
}

int main()
{
    string s;
    getline(cin, s);
    cout << calculateWithValues(s) << endl;
    // cout<<InfixToPostix(s)<<endl;
}