#include <iostream>
#include <cstddef>

/* helper functions(realization after main) */
template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal);
template <typename Type>
void deallocArr(Type* arr);
void printCombination(unsigned int permutation[], std::size_t size);

/* actual solution function */
void generateCombinations(std::size_t pos, unsigned int prev, std::size_t k, std::size_t n, unsigned int curr_combination[])
{
    if (pos == k) {
        printCombination(curr_combination, k);
        return;
    }

    for (std::size_t i = prev; i < n; ++i) {
        curr_combination[pos] = i + 1;
        generateCombinations(pos + 1, i + 1, k, n, curr_combination);
    }
}

int main()
{
    /* Natural number n */
    unsigned int n, k;
    std::cin >> n >> k;
    
    /* Array used for generating the combinations */
    unsigned int* combination = allocArr<unsigned int>(k, 0);

    /* Actual solution */
    generateCombinations(0, 0, k, n, combination);

    /* Free the arrays */
    deallocArr<unsigned int>(combination);

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
void printCombination(unsigned int combination[], std::size_t size)
{
    std::cout << combination[0];
    for (std::size_t i = 1; i < size; ++i)
        std::cout << ' ' << combination[i];
    std::cout << std::endl;
}