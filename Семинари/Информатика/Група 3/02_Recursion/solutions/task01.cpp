#include <iostream>

double quick_pow(double x, int n) {
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        return 1 / quick_pow(x, -n);
    }

    if (n % 2 == 0) {
        return quick_pow(x * x, n / 2);
    }
    return x * quick_pow(x, n - 1);
}

int main() {
   std::cout << quick_pow(3, 6) << std::endl;

    return 0;
}
