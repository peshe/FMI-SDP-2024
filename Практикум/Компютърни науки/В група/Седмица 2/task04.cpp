#include <iostream>
#include <cassert>
#include <bitset>

const int MAX_N = 128;

int main()
{
    std::bitset<MAX_N> fr1(0), fr2(0);
    unsigned int n, a, m1, m2;

    std::cin >> n >> m1 >> m2;

    for (int i = 1; i <= m1; ++i)
    {
        std::cin >> a;
        assert(1 <= a && a <= n);
        fr1[a] = true;
    }
    for (int i = 1; i <= m2; ++i)
    {
        std::cin >> a;
        assert(1 <= a && a <= n);
        fr2[a] = true;
    }

    std::cout << (fr1 & fr2).count() << std::endl;

    return 0;
}