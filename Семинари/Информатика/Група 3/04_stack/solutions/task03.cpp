#include <iostream>
#include <stack>

bool isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

char getCorrespondingOpeningBracket(char ch) {
    switch (ch) {
        case ')':
            return '(';

        case ']':
            return '[';

        case '}':
            return '{';
    }

    return '\0';
}

bool isValid(const std::string &s) {
    std::stack<char> stack;

    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (isOpeningBracket(*it)) {
            stack.push(*it);
        } else {
            if (!stack.empty() &&
                stack.top() == getCorrespondingOpeningBracket(*it)) {
                stack.pop();
            } else {
                return false;
            }
        }
    }

    return stack.empty();
}

int main() {
    std::string s1 = "{[()]()}", s2 = "[", s3 = "}", s4 = "", s5 = "()()()", s6 = "([)]";

    std::cout << std::boolalpha << isValid(s1) << std::endl;
    std::cout << std::boolalpha << isValid(s2) << std::endl;
    std::cout << std::boolalpha << isValid(s3) << std::endl;
    std::cout << std::boolalpha << isValid(s4) << std::endl;
    std::cout << std::boolalpha << isValid(s5) << std::endl;
    std::cout << std::boolalpha << isValid(s6) << std::endl;
}
