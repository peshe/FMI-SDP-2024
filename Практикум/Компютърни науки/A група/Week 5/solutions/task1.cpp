#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int num, k;
    cin >> k;
    cin >> num;
    stack<int> numStack;

    num *= 10;

    while (num > 0)
    {
        numStack.push(num % 10);
        num /= 10;
    }

    stack<int> result;
    result.push(numStack.top());
    numStack.pop();

    while (!numStack.empty())
    {
        int topResult = result.top();
        while (topResult > numStack.top() && k && !result.empty())
        {
            result.pop();
            if (!result.empty())
                topResult = result.top();
            k--;
        }
        result.push(numStack.top());
        numStack.pop();
    }

    result.pop();

    int resultNum = 0;
    int power = 1;
    while (!result.empty())
    {
        resultNum += result.top() * power;
        power *= 10;
        result.pop();
    }
    cout << resultNum;
}