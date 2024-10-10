#include <iostream>

void printSumTriangle(int arr[], std::size_t size) {
    if (size == 1) {
        std::cout << arr[0] << std::endl;
        return;
    }

    int *newArr = new int[size - 1];
    for (std::size_t i = 0; i < size - 1; ++i) {
        newArr[i] = arr[i] + arr[i + 1];
    }

    printSumTriangle(newArr, size - 1);

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
    delete[] newArr;
}
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    printSumTriangle(arr, 5);

    return 0;
}
