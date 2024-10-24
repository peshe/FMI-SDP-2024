#include <iostream>
#include <cassert>
#include <bitset>

const int MAX_N = 1024;

int main()
{
    std::bitset<MAX_N> bset(0);
    unsigned int n, a;

    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a;
        assert(a <= 1000);
        bset[a] = true;
    }

    std::cout << bset.count() << std::endl;

    return 0;
}