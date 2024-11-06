#include <iostream>
#include <stack>

template <typename Type>
void print(const std::stack<Type>& st)
{
    std::stack<Type> temp = st;

    while (!temp.empty())
    {
        std::cout << temp.top() << ' ';
        temp.pop();
    }
    std::cout << '\n';

    return;
}

template <typename Type>
void reverse(std::stack<Type>& st)
{
    std::stack<Type> temp;
    
    while (!st.empty())
    {
        Type curr = st.top();
        st.pop();
        temp.push(curr);
    }

    st = temp;

    return;
}

int main()
{
    std::stack<int> st;
    int i = 10;
    while (i > 0){
        st.push(i);
        --i;
    }
    print<int>(st);

    reverse<int>(st);

    print<int>(st);

    return 0;
}