#include <iostream>
#include <cstddef>

/* helper functions(realization after main) */
template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal);
template <typename Type>
void deallocArr(Type* arr);
void printSum(unsigned int sum[], std::size_t size);

/* actual solution function */
void generateSolutions(
    int currentSum, unsigned int sum[],
    std::size_t curr_idx,
    unsigned int denoms[], std::size_t size
) {
    if (currentSum == 0) printSum(sum, curr_idx);
    if (currentSum <= 0) return;

    for (int i = size - 1; i >= 0; --i) {
        if (
            currentSum - denoms[i] >= 0 &&
            sum[curr_idx - 1] >= denoms[i]
        ) {
            sum[curr_idx] = denoms[i];
            generateSolutions(
                currentSum - denoms[i], sum,
                curr_idx + 1,
                denoms, size
            );
        }
    }
}


int main()
{
    unsigned int n, k;
    std::cin >> n >> k;

    /* array for the denominations */
    unsigned int* denoms = allocArr<unsigned int>(k, 0);
    for (std::size_t i = 0; i < k; ++i) std::cin >> denoms[i];
    /* array where the answers are generated */
    unsigned int* sum = allocArr<unsigned int>(n + 1, 0);
    /* setting initially the first value to implement our algorithm */
    sum[0] = n + 1;

    /* solution */
    generateSolutions(n, sum, 1, denoms, k);
    
    deallocArr<unsigned int>(denoms);
    deallocArr<unsigned int>(sum);

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
void printSum(unsigned int sum[], std::size_t size)
{
    std::cout << sum[1];
    for (std::size_t i = 2; i < size; ++i)
        std::cout << " + " << sum[i];
    std::cout << std::endl;
}