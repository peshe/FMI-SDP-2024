#include <iostream>
#include <queue>
#include <string>


void printFirstNBinaryNumbers(unsigned n) {
    std::queue<std::string> nextNumbers;
    nextNumbers.push("1");

    for (unsigned i = 1; i <= n; ++i) {
        std::string currentNumber = nextNumbers.front();
        nextNumbers.pop();
        std::cout << currentNumber << ' ';

        nextNumbers.push(currentNumber + '0');
        nextNumbers.push(currentNumber + '1');
	}
    std::cout << std::endl;
}

int main() {
    printFirstNBinaryNumbers(10);
    printFirstNBinaryNumbers(31);

    return 0;
}
