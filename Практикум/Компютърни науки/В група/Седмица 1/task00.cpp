#include <iostream>

// a_0 = 1, a_1 = 2, a_n = 3a_n-1 + a_n-2

int findNth(int n)
{
    // Base cases:
    if (n == 0) return 1;
    if (n == 1) return 2;

    // Recursive calls:
    return 3 * findNth(n - 1) + findNth(n - 2); 
} 

int main()
{
    std::cout << findNth(5) << std::endl;

    return 0;
}