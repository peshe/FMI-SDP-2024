#include <iostream>
#include <cstddef>

/* helper functions(realization after main) */
template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal);
template <typename Type>
void deallocArr(Type* arr);
void printPermutation(unsigned int permutation[], std::size_t size);

/* actual solution function */
void generatePermutations(std::size_t pos, std::size_t n, unsigned int curr_permutation[], bool used[])
{
    if (pos == n) {
        printPermutation(curr_permutation, n);
        return;
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (used[i] == false) {
            used[i] = true;
            
            curr_permutation[pos] = i + 1;
            generatePermutations(pos + 1, n, curr_permutation, used);
            
            used[i] = false;
        }
    }
}

int main()
{
    /* Natural number n */
    unsigned int n;
    std::cin >> n;
    
    /* Arrays that are used for generating the permutations */
    unsigned int* permutation = allocArr<unsigned int>(n, 0);
    bool* used = allocArr<bool>(n, false);

    /* Actual solution */
    generatePermutations(0, n, permutation, used);

    /* Free the arrays */
    deallocArr<unsigned int>(permutation);
    deallocArr<bool>(used);

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
void printPermutation(unsigned int permutation[], std::size_t size)
{
    std::cout << permutation[0];
    for (std::size_t i = 1; i < size; ++i)
        std::cout << ' ' << permutation[i];
    std::cout << std::endl;
}