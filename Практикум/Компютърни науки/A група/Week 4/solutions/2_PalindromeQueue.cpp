#include <iostream>
#include <deque>
#include <algorithm>

bool isPalindrome(const std::deque<int>& dq) {
    auto front = dq.begin();
    auto back = dq.end() - 1;

    while (front < back) {
        if (*front != *back) {
            return false;
        }
        ++front;
        --back;
    }
    return true;
}

int main() {
    std::deque<int> dq1 = {1, 2, 3, 2, 1};
    std::deque<int> dq2 = {1, 2, 3, 4, 1};

    std::cout << std::boolalpha;
    std::cout << "dq1 палиндром: " << isPalindrome(dq1) << std::endl;
    std::cout << "dq2 палиндром: " << isPalindrome(dq2) << std::endl;

    return 0;
}
