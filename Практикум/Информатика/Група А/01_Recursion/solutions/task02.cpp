#include <iostream>

int pFibonacci(int i, int p) {
    if (i == p) {
        return 1;
    }

    if (i < p) {
        return 0;
    }

    int sum = 0;
    for (int j = 1; j <= p + 1; j++) {
        sum += pFibonacci(i - j, p);
    }

    return sum;
}

int main() {
    std::cout << pFibonacci(4, 3) << std::endl;
    std::cout << pFibonacci(10, 5) << std::endl;
    return 0;
}
