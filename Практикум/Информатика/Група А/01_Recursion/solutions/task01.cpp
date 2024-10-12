#include <iostream>

int reverse(int number, int result = 0) {
    if (number == 0) {
        return result;
    }
    return reverse(number / 10, result * 10 + number % 10);
}

bool isPalindrome(int number) {
    if (number < 0) {
        return false;
    }
    return reverse(number) == number;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << isPalindrome(1234) << std::endl;
    std::cout << isPalindrome(112211) << std::endl;
    return 0;
}
