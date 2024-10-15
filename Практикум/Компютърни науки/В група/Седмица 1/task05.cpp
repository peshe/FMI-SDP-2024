#include <iostream>
#include <cstddef>
#include <cmath>

/* helper functions(realization after main) */
template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal);
template <typename Type>
void deallocArr(Type* arr);

bool isValid(int x, int n)
{
    return x >= 0 && x < n;
}

int findMax(int** matr, int i, int j, int n)
{
    if (!isValid(i, n) || !isValid(j, n)) return 0;
    return matr[i][j] + std::max(findMax(matr, i + 1, j, n), findMax(matr, i + 1, j + 1, n));
}

int main()
{
    unsigned int n;
    std::cin >> n;

    /* Allocating and reading numbers */
    int** triangular_matr = allocArr<int*>(n, nullptr);
    for (std::size_t i = 0; i < n; ++i) {
        triangular_matr[i] = allocArr<int>(i + 1, 0);

        for (std::size_t j = 0; j < i + 1; ++j)
            std::cin >> triangular_matr[i][j];
    }
    /* Printing the matrix */
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < i; ++j)
            std::cout << triangular_matr[i][j] << ' ';
        std::cout << triangular_matr[i][i] << '\n';
    }

    std::cout << "The maximum path sum is " << findMax(triangular_matr, 0, 0, n) << std::endl;

    /* Deallocating the memory */
    for (std::size_t i = 0; i < n; ++i)
        deallocArr<int>(triangular_matr[i]);
    deallocArr<int*>(triangular_matr);
    
    return 0;
}

template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal)
{
    Type* arr = new Type[size];
    /* We do not handle the case where new fails
       cause this is not the focus of the problem */
    for (std::size_t i = 0; i < size; ++i)
        arr[i] = initVal;

    return arr;
}
template <typename Type>
void deallocArr(Type* arr)
{
    delete[] arr;
}