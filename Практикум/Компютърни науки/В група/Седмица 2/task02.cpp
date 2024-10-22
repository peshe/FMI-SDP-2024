#include <iostream>
#include <cstddef>
#include <bitset>

const int MAX_N = 1024;

int main()
{
    std::bitset<MAX_N> primes;
    primes.set();
    unsigned int n;
    std::cin >> n;

    primes[0] = primes[1] = false;
    for (std::size_t i = 2; i <= n; ++i) {
        if (primes.test(i)) {
            std::cout << i << ' ';

            for (std::size_t j = 2 * i; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }
    std::cout << std::endl;

    return 0;
}