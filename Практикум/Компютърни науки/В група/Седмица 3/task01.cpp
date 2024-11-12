#include <iostream>
#include <stack>
#include <string>
#include <cstddef>

bool isPalim(const std::string& input)
{
    std::stack<char> st;
    std::size_t middleIdx = input.size() / 2;
    
    for (std::size_t i = 0; i < middleIdx; ++i)
        st.push(input[i]);

    if (input.size() % 2 == 1) ++middleIdx;
    
    for (std::size_t i = middleIdx; i < input.size(); ++i)
        if (st.top() == input[i]) st.pop();
        else return false;

    return st.empty();
}
/*
0 1 2 3
1 2 3 4

0 1 2 3 4

*/

int main()
{
    std::string input;

    std::getline(std::cin, input);

    std::cout << isPalim(input) << std::endl;
    
    return 0;
}