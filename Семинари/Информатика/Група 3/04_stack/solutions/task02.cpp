#include <iostream>
#include <stack>

bool isPalindrome(const std::string &word) {
    if (word.empty() || word.size() == 1) {
        return true;
    }

    std::stack<char> st;
    for (std::size_t i = 0; i < word.size() / 2; ++i) {
        st.push(word[i]);
    }

    for (std::size_t i = (word.size() + 1) / 2; i < word.size(); ++i) {
        if (!st.empty() && st.top() == word[i]) {
            st.pop();
        } else {
            return false;
        }
    }

    return st.empty();
}

int main() {
    std::string s1 = "abcba", s2 = "abba", s3 = "aa", s4 = "a", s5 = "", s6 = "abaa";

    std::cout << std::boolalpha << isPalindrome(s1) << std::endl;
    std::cout << std::boolalpha << isPalindrome(s2) << std::endl;
    std::cout << std::boolalpha << isPalindrome(s3) << std::endl;
    std::cout << std::boolalpha << isPalindrome(s4) << std::endl;
    std::cout << std::boolalpha << isPalindrome(s5) << std::endl;
    std::cout << std::boolalpha << isPalindrome(s6) << std::endl;

    return 0;
}
