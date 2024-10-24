#include <iostream>

#include "DynamicStack.hpp"
#include "LinkedStack.hpp"

int main() {
    DynamicStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    std::cout << stack1.top() << std::endl;
    stack1.pop();
    std::cout << stack1.top() << std::endl;

    LinkedStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    std::cout << st.isEmpty() << std::endl;

    LinkedStack<int> st2(st);
    std::cout << st2.top() << std::endl;
    st2.pop();
    std::cout << "ONE: " << st.top() << std::endl;
    std::cout << "TWO: " << st2.top() << std::endl;

    return 0;
}