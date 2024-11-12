#include <iostream>
#include <queue>
#include <stack>
#include <cstddef>

template <typename Type>
void print(const std::queue<Type>& q)
{
    std::queue<Type> temp = q;

    while (!temp.empty())
    {
        std::cout << temp.front() << ' ';
        temp.pop();
    }
    std::cout << '\n';

    return;
}

template <typename Type>
void reverseFirstK(std::queue<Type>& q, std::size_t k)
{
    if (k > q.size()) return;

    std::stack<Type> st;
    for (std::size_t i = 0; i < k; ++i)
    {
        Type curr = q.front();
        q.pop();
        st.push(curr);
    }
    print(q);
    while (!st.empty())
    {
        q.push(st.top());
        st.pop();
    }

    std::size_t iters = q.size() - k;
    for (std::size_t i = 0; i < iters; ++i)
    {
        q.push(q.front());
        q.pop();
    }

    return;
}

int main()
{
    std::queue<int> q;
    int i = 1;
    while (i <= 10)
    {
        q.push(i);
        ++i;
    }
    print(q);
    reverseFirstK(q, 4);
    print(q);

    return 0;
}