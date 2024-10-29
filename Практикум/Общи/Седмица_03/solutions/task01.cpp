#include <iostream>
#include <stack>

void reverse(std::stack<int>& s)
{
    std::stack<int> temp;

    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    s = temp;
}

int main ()
{
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    reverse(s);

    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    return 0;
} 