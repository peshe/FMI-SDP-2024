#include <iostream>

int quickPow(int x, int n)
{
    if (n == 0) return 1;
    int y = x * x;

    return (
        n % 2 == 0 ?
        quickPow(y, n / 2) :
        x * quickPow(y, n / 2)
    );
}

int main()
{
    int x, n;
    std::cin >> x >> n;

    std::cout << quickPow(x, n) << std::endl;

    return 0;
}