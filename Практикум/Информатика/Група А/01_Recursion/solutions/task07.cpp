#include <iostream>
#include <vector>

void printStrings(const std::vector<char> &chars, const std::string &currentResult, std::size_t remainingCount) {
    if (remainingCount == 0) {
        std::cout << currentResult << std::endl;
        return;
    }

    for (std::size_t i = 0; i < chars.size(); ++i) {
        printStrings(chars, currentResult + chars[i], remainingCount - 1);
    }
}

int main() {
    const std::vector<char> chars = {'a', 'b'};
    printStrings(chars, "", 3);
    return 0;
}
